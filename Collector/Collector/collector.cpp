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
	rect.setY(ui.imageLabel->y() + 13);//magic number
	rect.setHeight(ui.imageLabel->height());	//###
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

	//###获取视频的种类
	videoType = proc.getVideoType(targetBaseName);

	//分割视频流成为帧图片
	proc.splitVideo(path, targetDir, targetBaseName);

	ui.pathLabel->setText(path);
	//start with existed db or new a db
	db.prepareDB(targetDir, videoType);
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

	//###获取视频的种类
	videoType = proc.getVideoType(targetBaseName);

	ui.pathLabel->setText(path);

	//start with existed db or new a db
	db.prepareDB(targetDir, videoType);
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

	//QShortcut *key_no_thumb = new QShortcut(QKeySequence(Qt::Key_S), this);//创建一个快捷键"T"键
	//connect(key_no_thumb, SIGNAL(activaed()), this, SLOT(on_autoThumbButt_clicked()));//链接到指定槽函数

	index = ui.lineEdit->text().toInt();
	updateWithIndex(index);
}

void Collector::on_endButt_clicked()
{
	db.convertDBtoTxt(targetDir, videoType);
	QMessageBox::information(NULL, tr("Finish!"), tr("Collection Finished! Please Check the Label txt File!"));
}

void Collector::on_lastButt_clicked()
{
	recordDataIntoDb(videoType);

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

	recordDataIntoDb(videoType);

	//move to next index
	index++;
	if (index >= maxCount)
	{
		QMessageBox::information(NULL, tr(""), tr("Arrive Maximal Index!"));
		return;
	}
	updateWithIndex(index);
}

void Collector::on_passButt_clicked()
{
	recordPassDataIntoDb();
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
	proc.addCircleInImage(posx, posy, videoType, imgWidget);

	//###由于存在双手的情况，将imgWidget->isOn = false;语句放到addCircleInImage函数的内部，视具体情况而定。
	//if (proc.clickedTimes>=2)
	//	imgWidget->isOn = false;

	displayMat(proc.showDstImage());
	displayData();
}

void Collector::recordDataIntoDb(QString videoType)
{
	displayMat(proc.showDstImage());
	displayData();

	if (!proc.hasFinished)
		return;

	//if check ok, record; else restart
	if (proc.checkPoints(videoType))
	{
		vector<float> params;
		//###
		if (videoType == "SingleOne")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
		}
		else if (videoType == "SingleTwo")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
		}
		else if (videoType == "SingleThree")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
		}
		else if (videoType == "SingleFour")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
		}
		else if (videoType == "SingleFive")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);
		}
		else if (videoType == "SingleSix")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);
		}
		else if (videoType == "SingleSeven")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);
		}
		else if (videoType == "SingleEight")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);
		}
		else if (videoType == "SingleNine")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
		}
		else if (videoType == "SingleGood")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);
		}
		else if (videoType == "SingleBad")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);
		}
		else if (videoType == "PairSix")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);

			float tlx_l = proc.tlx_l / FRAME_WIDTH; params.push_back(tlx_l);
			float tly_l = proc.tly_l / FRAME_HEIGHT; params.push_back(tly_l);
			float brx_l = proc.brx_l / FRAME_WIDTH; params.push_back(brx_l);
			float bry_l = proc.bry_l / FRAME_HEIGHT; params.push_back(bry_l);
			float iftx_l = proc.iftx_l / FRAME_WIDTH; params.push_back(iftx_l);
			float ifty_l = proc.ifty_l / FRAME_HEIGHT; params.push_back(ifty_l);
			float ifjx_l = proc.ifjx_l / FRAME_WIDTH; params.push_back(ifjx_l);
			float ifjy_l = proc.ifjy_l / FRAME_HEIGHT; params.push_back(ifjy_l);
		}
		else if (videoType == "PairSeven")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);

			float tlx_l = proc.tlx_l / FRAME_WIDTH; params.push_back(tlx_l);
			float tly_l = proc.tly_l / FRAME_HEIGHT; params.push_back(tly_l);
			float brx_l = proc.brx_l / FRAME_WIDTH; params.push_back(brx_l);
			float bry_l = proc.bry_l / FRAME_HEIGHT; params.push_back(bry_l);
			float iftx_l = proc.iftx_l / FRAME_WIDTH; params.push_back(iftx_l);
			float ifty_l = proc.ifty_l / FRAME_HEIGHT; params.push_back(ifty_l);
			float ifjx_l = proc.ifjx_l / FRAME_WIDTH; params.push_back(ifjx_l);
			float ifjy_l = proc.ifjy_l / FRAME_HEIGHT; params.push_back(ifjy_l);
			float mftx_l = proc.mftx_l / FRAME_WIDTH; params.push_back(mftx_l);
			float mfty_l = proc.mfty_l / FRAME_HEIGHT; params.push_back(mfty_l);
			float mfjx_l = proc.mfjx_l / FRAME_WIDTH; params.push_back(mfjx_l);
			float mfjy_l = proc.mfjy_l / FRAME_HEIGHT; params.push_back(mfjy_l);
		}
		else if (videoType == "PairEight")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);

			float tlx_l = proc.tlx_l / FRAME_WIDTH; params.push_back(tlx_l);
			float tly_l = proc.tly_l / FRAME_HEIGHT; params.push_back(tly_l);
			float brx_l = proc.brx_l / FRAME_WIDTH; params.push_back(brx_l);
			float bry_l = proc.bry_l / FRAME_HEIGHT; params.push_back(bry_l);
			float iftx_l = proc.iftx_l / FRAME_WIDTH; params.push_back(iftx_l);
			float ifty_l = proc.ifty_l / FRAME_HEIGHT; params.push_back(ifty_l);
			float ifjx_l = proc.ifjx_l / FRAME_WIDTH; params.push_back(ifjx_l);
			float ifjy_l = proc.ifjy_l / FRAME_HEIGHT; params.push_back(ifjy_l);
			float mftx_l = proc.mftx_l / FRAME_WIDTH; params.push_back(mftx_l);
			float mfty_l = proc.mfty_l / FRAME_HEIGHT; params.push_back(mfty_l);
			float mfjx_l = proc.mfjx_l / FRAME_WIDTH; params.push_back(mfjx_l);
			float mfjy_l = proc.mfjy_l / FRAME_HEIGHT; params.push_back(mfjy_l);
			float btx_l = proc.btx_l / FRAME_WIDTH; params.push_back(btx_l);
			float bty_l = proc.bty_l / FRAME_HEIGHT; params.push_back(bty_l);
			float bjx_l = proc.bjx_l / FRAME_WIDTH; params.push_back(bjx_l);
			float bjy_l = proc.bjy_l / FRAME_HEIGHT; params.push_back(bjy_l);
		}
		else if (videoType == "PairNine")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);

			float tlx_l = proc.tlx_l / FRAME_WIDTH; params.push_back(tlx_l);
			float tly_l = proc.tly_l / FRAME_HEIGHT; params.push_back(tly_l);
			float brx_l = proc.brx_l / FRAME_WIDTH; params.push_back(brx_l);
			float bry_l = proc.bry_l / FRAME_HEIGHT; params.push_back(bry_l);
			float iftx_l = proc.iftx_l / FRAME_WIDTH; params.push_back(iftx_l);
			float ifty_l = proc.ifty_l / FRAME_HEIGHT; params.push_back(ifty_l);
			float ifjx_l = proc.ifjx_l / FRAME_WIDTH; params.push_back(ifjx_l);
			float ifjy_l = proc.ifjy_l / FRAME_HEIGHT; params.push_back(ifjy_l);
			float mftx_l = proc.mftx_l / FRAME_WIDTH; params.push_back(mftx_l);
			float mfty_l = proc.mfty_l / FRAME_HEIGHT; params.push_back(mfty_l);
			float mfjx_l = proc.mfjx_l / FRAME_WIDTH; params.push_back(mfjx_l);
			float mfjy_l = proc.mfjy_l / FRAME_HEIGHT; params.push_back(mfjy_l);
			float rftx_l = proc.rftx_l / FRAME_WIDTH; params.push_back(rftx_l);
			float rfty_l = proc.rfty_l / FRAME_HEIGHT; params.push_back(rfty_l);
			float rfjx_l = proc.rfjx_l / FRAME_WIDTH; params.push_back(rfjx_l);
			float rfjy_l = proc.rfjy_l / FRAME_HEIGHT; params.push_back(rfjy_l);
			float tftx_l = proc.tftx_l / FRAME_WIDTH; params.push_back(tftx_l);
			float tfty_l = proc.tfty_l / FRAME_HEIGHT; params.push_back(tfty_l);
			float tfjx_l = proc.tfjx_l / FRAME_WIDTH; params.push_back(tfjx_l);
			float tfjy_l = proc.tfjy_l / FRAME_HEIGHT; params.push_back(tfjy_l);
		}
		else if (videoType == "PairTen")
		{
			float tlx = proc.tlx / FRAME_WIDTH; params.push_back(tlx);
			float tly = proc.tly / FRAME_HEIGHT; params.push_back(tly);
			float brx = proc.brx / FRAME_WIDTH; params.push_back(brx);
			float bry = proc.bry / FRAME_HEIGHT; params.push_back(bry);
			float iftx = proc.iftx / FRAME_WIDTH; params.push_back(iftx);
			float ifty = proc.ifty / FRAME_HEIGHT; params.push_back(ifty);
			float ifjx = proc.ifjx / FRAME_WIDTH; params.push_back(ifjx);
			float ifjy = proc.ifjy / FRAME_HEIGHT; params.push_back(ifjy);
			float mftx = proc.mftx / FRAME_WIDTH; params.push_back(mftx);
			float mfty = proc.mfty / FRAME_HEIGHT; params.push_back(mfty);
			float mfjx = proc.mfjx / FRAME_WIDTH; params.push_back(mfjx);
			float mfjy = proc.mfjy / FRAME_HEIGHT; params.push_back(mfjy);
			float rftx = proc.rftx / FRAME_WIDTH; params.push_back(rftx);
			float rfty = proc.rfty / FRAME_HEIGHT; params.push_back(rfty);
			float rfjx = proc.rfjx / FRAME_WIDTH; params.push_back(rfjx);
			float rfjy = proc.rfjy / FRAME_HEIGHT; params.push_back(rfjy);
			float tftx = proc.tftx / FRAME_WIDTH; params.push_back(tftx);
			float tfty = proc.tfty / FRAME_HEIGHT; params.push_back(tfty);
			float tfjx = proc.tfjx / FRAME_WIDTH; params.push_back(tfjx);
			float tfjy = proc.tfjy / FRAME_HEIGHT; params.push_back(tfjy);
			float btx = proc.btx / FRAME_WIDTH; params.push_back(btx);
			float bty = proc.bty / FRAME_HEIGHT; params.push_back(bty);
			float bjx = proc.bjx / FRAME_WIDTH; params.push_back(bjx);
			float bjy = proc.bjy / FRAME_HEIGHT; params.push_back(bjy);

			float tlx_l = proc.tlx_l / FRAME_WIDTH; params.push_back(tlx_l);
			float tly_l = proc.tly_l / FRAME_HEIGHT; params.push_back(tly_l);
			float brx_l = proc.brx_l / FRAME_WIDTH; params.push_back(brx_l);
			float bry_l = proc.bry_l / FRAME_HEIGHT; params.push_back(bry_l);
			float iftx_l = proc.iftx_l / FRAME_WIDTH; params.push_back(iftx_l);
			float ifty_l = proc.ifty_l / FRAME_HEIGHT; params.push_back(ifty_l);
			float ifjx_l = proc.ifjx_l / FRAME_WIDTH; params.push_back(ifjx_l);
			float ifjy_l = proc.ifjy_l / FRAME_HEIGHT; params.push_back(ifjy_l);
			float mftx_l = proc.mftx_l / FRAME_WIDTH; params.push_back(mftx_l);
			float mfty_l = proc.mfty_l / FRAME_HEIGHT; params.push_back(mfty_l);
			float mfjx_l = proc.mfjx_l / FRAME_WIDTH; params.push_back(mfjx_l);
			float mfjy_l = proc.mfjy_l / FRAME_HEIGHT; params.push_back(mfjy_l);
			float rftx_l = proc.rftx_l / FRAME_WIDTH; params.push_back(rftx_l);
			float rfty_l = proc.rfty_l / FRAME_HEIGHT; params.push_back(rfty_l);
			float rfjx_l = proc.rfjx_l / FRAME_WIDTH; params.push_back(rfjx_l);
			float rfjy_l = proc.rfjy_l / FRAME_HEIGHT; params.push_back(rfjy_l);
			float tftx_l = proc.tftx_l / FRAME_WIDTH; params.push_back(tftx_l);
			float tfty_l = proc.tfty_l / FRAME_HEIGHT; params.push_back(tfty_l);
			float tfjx_l = proc.tfjx_l / FRAME_WIDTH; params.push_back(tfjx_l);
			float tfjy_l = proc.tfjy_l / FRAME_HEIGHT; params.push_back(tfjy_l);
			float btx_l = proc.btx_l / FRAME_WIDTH; params.push_back(btx_l);
			float bty_l = proc.bty_l / FRAME_HEIGHT; params.push_back(bty_l);
			float bjx_l = proc.bjx_l / FRAME_WIDTH; params.push_back(bjx_l);
			float bjy_l = proc.bjy_l / FRAME_HEIGHT; params.push_back(bjy_l);
		}
		else
		{
			abort();
		}
		db.execInsert(index, currentImageName, params, videoType);
	}
	else
	{
		QMessageBox::information(NULL, tr(""), tr("Error In Current Frame Collection, Please Redo It!"));
		proc.clickedTimes = 0;
		proc.hasFinished = false;

		updateWithIndex(index);
	}
}

void Collector::recordPassDataIntoDb()
{
	vector<float> params;
	//###
	if (videoType == "SingleOne")
	{
		params.insert(params.begin(), 8, 0.0);	//###插入8个0
	}
	else if (videoType == "SingleTwo")
	{
		params.insert(params.begin(), 12, 0.0);
	}
	else if (videoType == "SingleThree")
	{
		params.insert(params.begin(), 16, 0.0);
	}
	else if (videoType == "SingleFour")
	{
		params.insert(params.begin(), 20, 0.0);
	}
	else if (videoType == "SingleFive")
	{
		params.insert(params.begin(), 24, 0.0);
	}
	else if (videoType == "SingleSix")
	{
		params.insert(params.begin(), 12, 0.0);
	}
	else if (videoType == "SingleSeven")
	{
		params.insert(params.begin(), 16, 0.0);
	}
	else if (videoType == "SingleEight")
	{
		params.insert(params.begin(), 12, 0.0);
	}
	else if (videoType == "SingleNine")
	{
		params.insert(params.begin(), 8, 0.0);
	}
	else if (videoType == "SingleGood")
	{
		params.insert(params.begin(), 8, 0.0);
	}
	else if (videoType == "SingleBad")
	{
		params.insert(params.begin(), 8, 0.0);
	}
	else if (videoType == "PairSix")
	{
		params.insert(params.begin(), 32, 0.0);
	}
	else if (videoType == "PairSeven")
	{
		params.insert(params.begin(), 36, 0.0);
	}
	else if (videoType == "PairEight")
	{
		params.insert(params.begin(), 40, 0.0);
	}
	else if (videoType == "PairNine")
	{
		params.insert(params.begin(), 44, 0.0);
	}
	else if (videoType == "PairTen")
	{
		params.insert(params.begin(), 48, 0.0);
	}
	else
	{
		abort();
	}
	db.execInsert(index, currentImageName, params, videoType);
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

	vector<float> v = db.execSelect(index, currentImageName, videoType);
	if (v.size() == 0)//查询db返回空
		displayMat(proc.showDstImage());
	if (v.size() == db.getCorrectParamCcount(videoType))//查询db返回已有数据
		displayMat(proc.showRecordedImage(v, videoType));

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

	//###right hand
	QString tlxy = "TopLeft:(" + QString::number(proc.tlx) + "," + QString::number(proc.tly) + ")";
	ui.tlLabel->setText(tlxy);

	QString brxy = "BottomRight:(" + QString::number(proc.brx) + "," + QString::number(proc.bry) + ")";
	ui.brLabel->setText(brxy);

	QString iftxy = "IndexFingerTip:(" + QString::number(proc.iftx) + "," + QString::number(proc.ifty) + ")";
	ui.iftLabel->setText(iftxy);

	QString ifjxy = "IndexFingerJoint:(" + QString::number(proc.ifjx) + "," + QString::number(proc.ifjy) + ")";
	ui.ifjLabel->setText(ifjxy);

	QString mftxy = "MiddleFingerTip:(" + QString::number(proc.mftx) + "," + QString::number(proc.mfty) + ")";
	ui.mftLabel->setText(mftxy);

	QString mfjxy = "MiddleFingerJoint:(" + QString::number(proc.mfjx) + "," + QString::number(proc.mfjy) + ")";
	ui.mfjLabel->setText(mfjxy);

	QString rftxy = "RingFingerTip:(" + QString::number(proc.rftx) + "," + QString::number(proc.rfty) + ")";
	ui.rftLabel->setText(rftxy);

	QString rfjxy = "RingFingerJoint:(" + QString::number(proc.rfjx) + "," + QString::number(proc.rfjy) + ")";
	ui.rfjLabel->setText(rfjxy);

	QString tftxy = "TailFingerTip:(" + QString::number(proc.tftx) + "," + QString::number(proc.tfty) + ")";
	ui.tftLabel->setText(tftxy);

	QString tfjxy = "TailFingerJoint:(" + QString::number(proc.tfjx) + "," + QString::number(proc.tfjy) + ")";
	ui.tfjLabel->setText(tfjxy);

	QString btxy = "ThumbTip:(" + QString::number(proc.btx) + "," + QString::number(proc.bty) + ")";
	ui.btLabel->setText(btxy);

	QString bjxy = "ThumbJoint:(" + QString::number(proc.bjx) + "," + QString::number(proc.bjy) + ")";
	ui.bjLabel->setText(bjxy);

	//###left hand
	QString tlxy_l = "TopLeft:(" + QString::number(proc.tlx_l) + "," + QString::number(proc.tly_l) + ")";
	ui.tlLabel_l->setText(tlxy_l);

	QString brxy_l = "BottomRight:(" + QString::number(proc.brx_l) + "," + QString::number(proc.bry_l) + ")";
	ui.brLabel_l->setText(brxy_l);

	QString iftxy_l = "IndexFingerTip:(" + QString::number(proc.iftx_l) + "," + QString::number(proc.ifty_l) + ")";
	ui.iftLabel_l->setText(iftxy_l);

	QString ifjxy_l = "IndexFingerJoint:(" + QString::number(proc.ifjx_l) + "," + QString::number(proc.ifjy_l) + ")";
	ui.ifjLabel_l->setText(ifjxy_l);

	QString mftxy_l = "MiddleFingerTip:(" + QString::number(proc.mftx_l) + "," + QString::number(proc.mfty_l) + ")";
	ui.mftLabel_l->setText(mftxy_l);

	QString mfjxy_l = "MiddleFingerJoint:(" + QString::number(proc.mfjx_l) + "," + QString::number(proc.mfjy_l) + ")";
	ui.mfjLabel_l->setText(mfjxy_l);

	QString rftxy_l = "RingFingerTip:(" + QString::number(proc.rftx_l) + "," + QString::number(proc.rfty_l) + ")";
	ui.rftLabel_l->setText(rftxy_l);

	QString rfjxy_l = "RingFingerJoint:(" + QString::number(proc.rfjx_l) + "," + QString::number(proc.rfjy_l) + ")";
	ui.rfjLabel_l->setText(rfjxy_l);

	QString tftxy_l = "TailFingerTip:(" + QString::number(proc.tftx_l) + "," + QString::number(proc.tfty_l) + ")";
	ui.tftLabel_l->setText(tftxy_l);

	QString tfjxy_l = "TailFingerJoint:(" + QString::number(proc.tfjx_l) + "," + QString::number(proc.tfjy_l) + ")";
	ui.tfjLabel_l->setText(tfjxy_l);

	QString btxy_l = "ThumbTip:(" + QString::number(proc.btx_l) + "," + QString::number(proc.bty_l) + ")";
	ui.btLabel_l->setText(btxy_l);

	QString bjxy_l = "ThumbJoint:(" + QString::number(proc.bjx_l) + "," + QString::number(proc.bjy_l) + ")";
	ui.bjLabel_l->setText(bjxy_l);

}