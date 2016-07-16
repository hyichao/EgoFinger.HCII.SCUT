#include "collector.h"


Collector::Collector(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	//using self defined widget just for crossing lines
	QWidget *mainWindow = this->window();
	QLayout *layout = this->layout();
	imgWidget = new ImageWidget();
	imgWidget->isOn = false;
	QRect rect = ui.imageLabel->geometry();
	rect.setY(ui.imageLabel->y()+13);//magic number
	imgWidget->setGeometry(rect);
	layout->addWidget(imgWidget);
	mainWindow->setLayout(layout);
}

Collector::~Collector()
{

}

//*****************
// 点击按钮事件
//*****************
void Collector::on_videoButt_clicked()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Video"), tr(""));
	if (path.length() == 0)
	{
		QMessageBox::information(NULL, tr("Path"), tr("Didn't Select a Correct Video File."));
		return;
	}

	//利用视频文件获取路径
	QFileInfo fileInfo(path);
	targetBaseName = fileInfo.baseName();
	targetDir = fileInfo.path();

	//分割视频流成为帧图片
	proc.splitVideo(path, targetDir, targetBaseName);

	ui.pathLabel->setText(path);
	//start with existed db or new a db
	db.prepareDB(targetDir);
}

void Collector::on_selectButt_clicked()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Video"), tr(""));
	if (path.length() == 0)
	{
		QMessageBox::information(NULL, tr("Path"), tr("Didn't Select a Correct Video File."));
		return;
	}

	QFileInfo fileInfo(path);
	targetBaseName = fileInfo.baseName();//文件名（除去后缀）
	targetDir = fileInfo.path();//文件目录路径

	ui.pathLabel->setText(path);

	//start with existed db or new a db
	db.prepareDB(targetDir);
}

void Collector::on_startButt_clicked()
{
	if (targetDir.length() == 0)
	{
		QMessageBox::information(NULL, tr("Empty Path"), tr("Pleass Open a Directory!"));
		return;
	}

	//calculate the number of files
	QDir dir(targetDir);
	if (!dir.exists()) 
		return;
	dir.setFilter(QDir::Files | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();

	int file_count = list.count();
	if (file_count <= 0)
		return;

	minCount = 0;
	maxCount = file_count;

	//shortcut of pre butt
	QShortcut *key_pre = new QShortcut(QKeySequence(Qt::Key_A), this);//创建一个快捷键"A"键
	connect(key_pre, SIGNAL(activated()), this, SLOT(on_lastButt_clicked()));//连接到指定槽函数

	//shortcut of next butt
	QShortcut *key_next = new QShortcut(QKeySequence(Qt::Key_D), this);//创建一个快捷键"D"键
	connect(key_next, SIGNAL(activated()), this, SLOT(on_nextButt_clicked()));//连接到指定槽函数

	QShortcut *key_no_thumb = new QShortcut(QKeySequence(Qt::Key_S), this);//创建一个快捷键"T"键
	connect(key_no_thumb, SIGNAL(activaed()), this, SLOT(on_autoThumbButt_clicked()));//链接到指定槽函数

	index = ui.lineEdit->text().toInt();
	updateWithIndex(index);
}

void Collector::on_endButt_clicked()
{
	db.convertDBtoTxt(targetDir);
	QMessageBox::information(NULL, tr("Finish!"), tr("Collection Finished! Please Check the Label txt File!"));
}

void Collector::on_lastButt_clicked()
{
	if (proc.clickedTimes == 5)
	{
		int ttx = 0; int tty = 0;
		int tjx = 0; int tjy = 0;

		proc.addCircleInImage(ttx, tty);
		proc.addCircleInImage(tjx, tjy);

		recordDataIntoDb();
	}
	else if (proc.clickedTimes == 7){
		recordDataIntoDb();
	}

	//move to previous index
	index--;
	if (index < minCount)
	{
		QMessageBox::information(NULL, tr(""), tr("Arrived Minimal Index!"));
		index = minCount;
		return;
	}

	updateWithIndex(index);
}

void Collector::on_nextButt_clicked()
{

	if (proc.clickedTimes == 5)
	{
		int ttx = 0; int tty = 0;
		int tjx = 0; int tjy = 0;

		proc.addCircleInImage(ttx, tty);
		proc.addCircleInImage(tjx, tjy);

		recordDataIntoDb();
	}
	else if (proc.clickedTimes == 7){
		recordDataIntoDb();
	}

	//move to next index
	index++;
	if (index >= maxCount)
	{
		QMessageBox::information(NULL, tr(""), tr("Arrive Maximal Index!"));
		return;
	}
	updateWithIndex(index);
}


//*****************
// 鼠标事件
//*****************
void Collector::mousePressEvent(QMouseEvent *e)
{
	//get coordinate inside label
	int posx = e->x();
	int posy = e->y();

	posx -= (ui.imageLabel->x());
	posy -= (ui.imageLabel->y() + ui.mainToolBar->height());

	//return if out
	if (posx>FRAME_WIDTH || posy > FRAME_HEIGHT || posx < 0 || posy < 0)
		return;

	//circle it out
	proc.addCircleInImage(posx, posy);

	if (proc.clickedTimes>=2)
		imgWidget->isOn = false;

	displayMat(proc.showDstImage());
	displayData();
}

void Collector::recordDataIntoDb()
{
	displayMat(proc.showDstImage());
	displayData();

	if (!proc.hasFinished)
		return;

	//if check ok, record; else restart
	if (proc.checkPoints())
	{
		vector<float> params;
		float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
		float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
		float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
		float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
		float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
		float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
		float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
		float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
		float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
		float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
		float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
		float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
		float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
		float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);

		db.execInsert(index, currentImageName, params);
	}
	else
	{
		QMessageBox::information(NULL, tr(""), tr("Error In Current Frame Collection, Please Redo It!"));
		proc.clickedTimes = 0;
		proc.hasFinished = false;

		updateWithIndex(index);
	}
}



//*****************
// 基于序号index更新视图
//*****************
void Collector::updateWithIndex(int currentIndex)
{
	//get current file
	currentImageName = targetBaseName + "_color_" + QString::number(currentIndex) + ".png";
	QString imageInPath = targetDir + "/" + currentImageName;
	proc.readImage(imageInPath.toStdString().data());

	imgWidget->isOn = true;

	vector<float> v = db.execSelect(index,currentImageName);
	if (v.size() == 0)//查询db返回空
		displayMat(proc.showDstImage());
	if (v.size() == COLLECT_PARAM_COUNT)//查询db返回已有数据
		displayMat(proc.showRecordedImage(v));

	displayData();
}

//*****************
// 数据结构转化：OpenCV vs Qt
// 输出图片到QtLabel
//*****************
void Collector::displayMat(Mat image)
{
	Mat rgb;
	QImage img;
	if (image.channels() == 3)
	{
		//cvt Mat BGR 2 QImage RGB
		cvtColor(image, rgb, CV_BGR2RGB);
		img = QImage((const unsigned char*)(rgb.data),
			rgb.cols, rgb.rows,
			rgb.cols*rgb.channels(),
			QImage::Format_RGB888);
	}
	else
	{
		img = QImage((const unsigned char*)(image.data),
			image.cols, image.rows,
			image.cols*image.channels(),
			QImage::Format_RGB888);
	}

	ui.imageLabel->setPixmap(QPixmap::fromImage(img));
	ui.imageLabel->resize(ui.imageLabel->pixmap()->size());
}

void Collector::displayData()
{
	QString imageInPath = "/" + targetBaseName + "_color_" + QString::number(index) + ".png";
	ui.fileNameLabel->setText(imageInPath);

	QString tlxy = "TopLeft:(" + QString::number(proc.tlx) + "," + QString::number(proc.tly) + ")";
	ui.tlLabel->setText(tlxy);

	QString brxy = "BottomRight:(" + QString::number(proc.brx) + "," + QString::number(proc.bry) + ")";
	ui.brLabel->setText(brxy);

	QString iftxy = "IndexFingertip:(" + QString::number(proc.iftx) + "," + QString::number(proc.ifty) + ")";
	ui.iftLabel->setText(iftxy);

	QString ifjxy = "IndexFingerJoint:(" + QString::number(proc.ifjx) + "," + QString::number(proc.ifjy) + ")";
	ui.ifjLabel->setText(ifjxy);

	QString tfjxy = "TailFingerJoint:(" + QString::number(proc.ifjx) + "," + QString::number(proc.ifjy) + ")";
	ui.tfjLabel->setText(tfjxy);

	QString btxy = "ThumbTip:(" + QString::number(proc.btx) + "," + QString::number(proc.bty) + ")";
	ui.btLabel->setText(btxy);

	QString bjxy = "ThumbJoint:(" + QString::number(proc.bjx) + "," + QString::number(proc.bjy) + ")";
	ui.bjLabel->setText(bjxy);


}