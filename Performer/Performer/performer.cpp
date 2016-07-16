#include "performer.h"
#include "common.h"

Performer::Performer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Performer::~Performer()
{

}


//*****************
// Usage£º
// 1. choose color space and box type
// 2. click button
//*****************
void Performer::on_colorDistButt_clicked()
{
	QString imageDir = pathManager.getDir();
	QString txtPath = pathManager.getFile();
	QString targetPath = pathManager.getTargetDir();
	DistributionType type = (DistributionType)ui.typeComboBox->currentIndex();
	ColorSpace colorSpace = (ColorSpace)ui.spaceComboBox->currentIndex();

	string dir = imageDir.toStdString().data();
	string inTxt = txtPath.toStdString().data();
	
	ColorDistribution colorDistribution;
	colorDistribution.init(dir, inTxt, type, colorSpace);
	colorDistribution.calcHistogram();
	colorDistribution.showHistogram();
}

//*****************
// Usage£º
// 1. Click button
//*****************
void Performer::on_posDistButt_clicked()
{
	BoxDistribution distribution;
	string txtPath = pathManager.getFile().toStdString().data();
	distribution.showFrequencyMat(txtPath);
}


//*****************
// Usage£º
// 1. Choose point
// 2. Click Button
//*****************
void Performer::on_moveDistButt_clicked()
{
	MovementDetector detector;

	PointType type = (PointType)ui.typeComboBox->currentIndex();
	string path = pathManager.getFile().toStdString().data();

	detector.setTxtPath(path);
	detector.showMovementHistogram(type);
}

//*****************
// Usage£º
// 1. Click button
//*****************
void Performer::on_fingerLengthButt_clicked()
{
	FingerLength length;
	string path = pathManager.getFile().toStdString().data();
	length.setPath(path);
	length.displayHistogram();

}

//*****************
// Usage£º
// 1. Click button
//*****************
void Performer::on_pointingDirButt_clicked()
{
	PointingDirection pointing;
	string path = pathManager.getFile().toStdString().data();
	pointing.setPath(path);
	pointing.displayHistogram();
}


//*****************
// Usage:
// 1. Click Button
//*****************
void Performer::on_frameDiffButt_clicked()
{
	FrameDifference diff;

	QString imageDir = pathManager.getDir();
	QString txtPath = pathManager.getFile();
	QString targetPath = pathManager.getTargetDir();

	diff.setOrder(1);				//FIXME hard code of order
	diff.showFrameDifference(imageDir, txtPath, targetPath);
}

//*****************
// Usage:
// 1. Generate Frame Difference Images
// 2. Click Button
//*****************
void Performer::on_saliencyButt_clicked()
{
	SaliencyDetector detector;
	QString path = pathManager.getTargetDir();
	detector.displaySaliencySequence(path);
}

void Performer::on_errorButt_clicked()
{
	ErrorAnalyzer analyzer;
	analyzer.setImageDir("F:/Benchmark/ErrorAnalysis/HCIILab");
	analyzer.setTxtDir("F:/Benchmark/ErrorAnalysis");

	analyzer.showImageWithMultiPoints(0);
}


//*****************
// Choose the Directory of Images
// Choose the path of txt file
//*****************

void Performer::on_dirButt_clicked()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), tr(""));
	if (path.length() == 0)
	{
		QMessageBox::information(NULL, tr("Path"), tr("Didn't Select a Correct Video File."));
		return;
	}

	pathManager.setDir(path);

	ui.dirLabel->setText(pathManager.getDir());
}

void Performer::on_fileButt_clicked()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""));
	if (path.length() == 0)
	{
		QMessageBox::information(NULL, tr("Path"), tr("Didn't Select a Correct Video File."));
		return;
	}

	pathManager.setFile(path);

	ui.txtLabel->setText(pathManager.getFile());
}




//*****************
// Convert data structure£ºOpenCV vs Qt
// Output image to label
//*****************
//void Performer::displayBGRMat(Mat image)
//{
//	Mat rgb;
//	QImage img;
//	if (image.channels() == 3)
//	{
//		//cvt Mat BGR 2 QImage RGB
//		cvtColor(image, rgb, CV_BGR2RGB);
//		img = QImage((const unsigned char*)(rgb.data),
//			rgb.cols, rgb.rows,
//			rgb.cols*rgb.channels(),
//			QImage::Format_RGB888);
//	}
//	else
//	{
//		img = QImage((const unsigned char*)(image.data),
//			image.cols, image.rows,
//			image.cols*image.channels(),
//			QImage::Format_RGB888);
//	}
//
//	ui.imageLabel->setPixmap(QPixmap::fromImage(img));
//	ui.imageLabel->resize(ui.imageLabel->pixmap()->size());
//}