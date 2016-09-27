#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWithArgv(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;

    loadGestureImages();

    QShortcut *key_quit = new QShortcut(QKeySequence(Qt::Key_Q),this);
    connect(key_quit,SIGNAL(activated()),this,SLOT(on_quitButton_clicked()));

    QShortcut *key_air = new QShortcut(QKeySequence(Qt::Key_A),this);
    connect(key_air,SIGNAL(activated()),this,SLOT(on_writingButton_clicked()));

    QShortcut *key_det = new QShortcut(QKeySequence(Qt::Key_D),this);
    connect(key_det,SIGNAL(activated()),this,SLOT(on_trackingButton_clicked()));

    QShortcut *key_home = new QShortcut(QKeySequence(Qt::Key_H),this);
    connect(key_home,SIGNAL(activated()),this,SLOT(on_homeButton_clicked()));

    QShortcut *key_clear = new QShortcut(QKeySequence(Qt::Key_C),this);
    connect(key_clear,SIGNAL(activated()),this,SLOT(on_clearButton_clicked()));
}

void MainWindow::loadGestureImages(){
    QDir dir;
    QString path[6] = {
    "/resources/Close.png",
    "/resources/Open.png",
    "/resources/Lback.png",
    "/resources/Iback.png",
    "/resources/Victory.png",
    "/resources/Fist.png" };
    for (int i = 0; i < 6; ++i) {
        qDebug()<<dir.currentPath()+path[i];
        if(!gestureImage[i].load(dir.currentPath()+path[i])){
            qDebug()<<"Load image "<<dir.currentPath()+path[i]<<" failed.";
            LOG(FATAL)<<"Load image failed.";
        }
    }
}

void MainWindow::loopForward(bool isAirWriting)
{
    manager.init(this->argc,this->argv);
    manager.log_argv();
    manager.set_gpu_device();

    //********************************
    // prepare network
    //********************************
    Net<float>* net_hand = new Net<float>(manager.get_hand_proto(), caffe::TEST);
    shared_ptr<Net<float> > feature_extraction_net_hand(net_hand);
    feature_extraction_net_hand->CopyTrainedLayersFrom(manager.get_hand_caffemodel());

    Net<float>* net_finger = new Net<float>(manager.get_finger_proto(), caffe::TEST);
    shared_ptr<Net<float> > feature_extraction_net_finger(net_finger);
    feature_extraction_net_finger->CopyTrainedLayersFrom(manager.get_finger_caffemodel());

    //********************************
    // extraction loop
    //********************************
    processor.initCapture(manager.get_camera_id());
    controll.initStatus();

    std::vector<Blob<float>*> input_vec_hand;
    input_vec_hand.push_back(new Blob<float>);
    input_vec_hand[0]->Reshape(createBlobShape<float>(1,3,151,201));

    std::vector<Blob<float>*> input_vec_finger;
    input_vec_finger.push_back(new Blob<float>);
    input_vec_finger[0]->Reshape(createBlobShape<float>(2,3,65,65));

    while (processor.capture.isOpened()) {

      //********** hand detection ************
      processor.readFrame();
      vector<cv::Mat> srcs(1, processor.src);
      CvMats2blobVec<float>(srcs, input_vec_hand);

      //if using, make sure image_data_layer input correct
      feature_extraction_net_hand->Forward(input_vec_hand);
      const shared_ptr<Blob<float> > feature_blob_hand
              = feature_extraction_net_hand->blob_by_name(manager.get_hand_blob());
      const float* feature_blob_data_hand = feature_blob_hand->cpu_data();

      processor.output2TlBr(feature_blob_data_hand[0],feature_blob_data_hand[1],
              feature_blob_data_hand[2],feature_blob_data_hand[3],true,
              feature_blob_data_hand[4],true);

      //********** fingertip detection ************
      processor.cutDirectRoi();
      processor.cutRotatedRoi();

      vector<cv::Mat> rois;
      rois.push_back(processor.roi);
      rois.push_back(processor.rot_roi);
      CvMats2blobVec<float>(rois, input_vec_finger);
      feature_extraction_net_finger->Forward(input_vec_finger);
      const shared_ptr<Blob<float> > feature_blob_finger
          = feature_extraction_net_finger->blob_by_name(manager.get_finger_blob());
      const float* feature_blob_data_finger
          = feature_blob_finger->cpu_data();

      // predict point
      processor.output2FtJnt(feature_blob_data_finger[15],feature_blob_data_finger[16],
                             feature_blob_data_finger[17],feature_blob_data_finger[18],
                             false, true);

      // offset
      processor.attentionOffset();
      processor.updateTracker();
      // status predict and controll
      controll.calcCurrentStatus(feature_blob_data_finger,7);
      controll.switchStatus();

      if(isAirWriting)
        processor.render(writing,controll.status);
      else
        processor.render(controll.status);

      updateView();

      if(controll.judgeBackground())
          processor.reInitTrackcenter();

      cv::waitKey(1);
    }
}

void MainWindow::updateView()
{
    // show image on GUI
    updateImageLabel(processor.camera_output);

    // show gesture result on GUI
    if(controll.isShiftingStatus)
        updateGestureLabel(controll.status);

    int waitCount = 30;
    // show text on GUI
    if(controll.isRecognizing && controll.judgeOpen() && processor.recognizedCdd.size()>=30)
    {
        int which = (std::max(0,controll.recognizingCounter)%(waitCount*5))/waitCount;
        int cdd_size = 5;
        string cdd[cdd_size];
        for(int i=0;i<cdd_size;i++){
            cdd[i]=processor.recognizedCdd.substr(i*3*2,3);
        }

        processor.addUpRecognized(cdd[which]);
        processor.setRecognizedCdd("");

        controll.isRecognizing=false;
        controll.recognizingCounter=-15;

        updateTextLabel(processor.recognized);
        updateCandidateLabel(processor.recognizedCdd);
    }

    // show all candidates of Characters on GUI
    if(controll.judgeLback()){

        updateCandidateLabel(processor.recognizedCdd);

        controll.isRecognizing = true;
        controll.recognizingCounter++;

        int pos = (std::max(0,controll.recognizingCounter)%(waitCount*5))/waitCount;
        updateCandidateLabelColor(pos);
    }

    // for deleting character
    if(!controll.isDeleting && controll.judgeClose()){
        controll.isDeleting = true;

        int recogSize = processor.recognized.size();
        processor.recognized=(processor.recognized.substr(0,recogSize-3));
        updateTextLabel(processor.recognized);
    }
    if(controll.isDeleting && !controll.judgeClose()){
        controll.isDeleting = false;
    }
}

/**
 * @brief MainWindow::on_writingButton_clicked
 * For showing writing demo
 */
void MainWindow::on_writingButton_clicked()
{
    if(processor.capture.isOpened()){
        this->processor.capture.release();
        qDebug()<<"Release camera.";
    }
    processor.recognized="";
    processor.recognizedCdd="";
    loopForward(true);
}

/**
 * @brief MainWindow::on_trackingButton_clicked
 * For showing tracking demo
 */
void MainWindow::on_trackingButton_clicked()
{
    if(processor.capture.isOpened()){
        this->processor.capture.release();
        qDebug()<<"Release camera.";
    }
    processor.recognized="";
    processor.recognizedCdd="";
    loopForward(false);
}


void MainWindow::on_homeButton_clicked()
{
    this->ui->imageLabel->clear();
    this->ui->gestureLabel->clear();
    this->ui->textLabel->clear();

    QImage homeImage;
    QDir currentDir;
    QString path = currentDir.currentPath()+"/resources/AwHome.png";
    qDebug()<<path;
    bool flag = homeImage.load(path);
    if(flag){
        homeImage = homeImage.scaled(960,720);
        this->ui->imageLabel->setPixmap(QPixmap::fromImage(homeImage));
        ui->imageLabel->resize(ui->imageLabel->pixmap()->size());
    } else {
        qDebug()<<"load home page fail";
    }

    this->ui->textLabel->clear();
    if(processor.capture.isOpened()){
        this->processor.capture.release();
        qDebug()<<"Release camera.";
    }
}

void MainWindow::on_quitButton_clicked(){
    if(processor.capture.isOpened()){
        this->processor.capture.release();
        qDebug()<<"Release camera.";
    }
    if(processor.writer.isOpened()){
        this->processor.writer.release();
        qDebug()<<"Release writer.";
    }
    exit(0);
}

void MainWindow::on_clearButton_clicked(){
    processor.recognized="";
    this->updateTextLabel(processor.recognized);
}

/**
 * @brief MainWindow::updateImageLabel
 * @param img
 * update QLabel with new cvMat
 */
void MainWindow::updateImageLabel(Mat img)
{
    //add effective zone
    int width = img.cols;
    int height = img.rows;
    cv::Rect rect(cv::Point(width*0.05,height*0.0),cv::Point(width*0.95,height*0.95));
    cv::rectangle(img,rect,COLOR_RED);

    //display cvmat on qlabel
    displayMat(img);
}

/**
 * @brief MainWindow::updateTextLabel
 * @param str
 * update QLabel with new text
 */
void MainWindow::updateTextLabel(string str)
{
    QPalette green_pallete;
    green_pallete.setColor(QPalette::WindowText,Qt::green);

    QString qstr = QString::fromStdString(str);
    ui->textLabel->clear();
    ui->textLabel->setPalette(green_pallete);
    ui->textLabel->setText(qstr);
}

void MainWindow::updateGestureLabel(GesStatus status)
{
    if(STATUS_BG != status){
        ui->gestureLabel->setPixmap(QPixmap::fromImage(gestureImage[status-1]));
        ui->gestureLabel->resize(ui->gestureLabel->pixmap()->size());
    }
    else{
        ui->gestureLabel->clear();
    }
}

void MainWindow::updateCandidateLabel(string cdds)
{
    if(cdds.length()<30){
        ui->label_1->clear();
        ui->label_2->clear();
        ui->label_3->clear();
        ui->label_4->clear();
        ui->label_5->clear();
        return;
    }
    int cdd_size = 5;
    string cdd[cdd_size];
    for(int i=0;i<cdd_size;i++){
        cdd[i]=cdds.substr(i*3*2,3);
    }
    ui->label_1->setText(QString::fromStdString(cdd[0]));
    ui->label_2->setText(QString::fromStdString(cdd[1]));
    ui->label_3->setText(QString::fromStdString(cdd[2]));
    ui->label_4->setText(QString::fromStdString(cdd[3]));
    ui->label_5->setText(QString::fromStdString(cdd[4]));
}

void MainWindow::updateCandidateLabelColor(int pos)
{
    QFont bigFont;
    bigFont.setPixelSize(100);
//    bigFont.setBold(true);
    QFont smallFont;
    smallFont.setPixelSize(80);

    QPalette red_pallete;
    red_pallete.setColor(QPalette::WindowText,Qt::red);

    QPalette green_pallete;
    green_pallete.setColor(QPalette::WindowText,Qt::green);

    ui->label_1->setPalette(red_pallete);  ui->label_1->setFont(smallFont);
    ui->label_2->setPalette(red_pallete);  ui->label_2->setFont(smallFont);
    ui->label_3->setPalette(red_pallete);  ui->label_3->setFont(smallFont);
    ui->label_4->setPalette(red_pallete);  ui->label_4->setFont(smallFont);
    ui->label_5->setPalette(red_pallete);  ui->label_5->setFont(smallFont);


    switch (pos) {
    case 0:
        ui->label_1->setPalette(green_pallete);
        ui->label_1->setFont(bigFont);
        break;
    case 1:
        ui->label_2->setPalette(green_pallete);
        ui->label_2->setFont(bigFont);
        break;
    case 2:
        ui->label_3->setPalette(green_pallete);
        ui->label_3->setFont(bigFont);
        break;
    case 3:
        ui->label_4->setPalette(green_pallete);
        ui->label_4->setFont(bigFont);
        break;
    case 4:
        ui->label_5->setPalette(green_pallete);
        ui->label_5->setFont(bigFont);
        break;
    default:
        break;
    }
}

/**
 * @brief MainWindow::displayMat
 * @param image
 * transform cvMat into QImage
 */
void MainWindow::displayMat(Mat image)
{
    Mat rgb;
    QImage img;
    if (image.channels() == 3)
    {
        //cvt Mat BGR 2 QImage RGB
        cv::resize(image,image,cv::Size(960,720));
        cvtColor(image, rgb, CV_BGR2RGB);
        img = QImage((const unsigned char*)(rgb.data),
            rgb.cols, rgb.rows,
            rgb.cols*rgb.channels(),
            QImage::Format_RGB888);
    }
    else
    {
        cv::resize(image,rgb,cv::Size(960,720));
        img = QImage((const unsigned char*)(image.data),
            image.cols, image.rows,
            image.cols*image.channels(),
            QImage::Format_RGB888);
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(img));
    ui->imageLabel->resize(ui->imageLabel->pixmap()->size());
}
