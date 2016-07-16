#include "FrameDifference.h"


FrameDifference::FrameDifference()
{
}


FrameDifference::~FrameDifference()
{
}

void FrameDifference::showFrameDifference(QString dir, QString txtPath, QString targetDir)
{
	string imageName;
	double unused;
	QStringList list;

	ifstream infile(txtPath.toStdString().data(), ios::in);
	if (!infile)
	{
		qDebug() << "Error! Empty File!! Pls Check File Path!";
		return;
	}

	while (
		infile >> imageName
		>> unused >> unused >> unused >> unused						// tl,br
		>> unused >> unused >> unused >> unused >> unused >> unused	// index finger and tail
		>> unused >> unused >> unused >> unused						// thumb
		)
	{
		QString imagePath = dir + "/" + imageName.data();
		list.append(imagePath);
	}

	int previous = -1;
	int next = previous + order;
	while (true)
	{
		previous++;
		next++;

		QString previousStr = list.at(previous);
		if (!setPreviousImg(previousStr.toStdString().data()))
			break;
		QString nextStr = list.at(next);
		if (!setNextImg(nextStr.toStdString().data()))
			break;

		//calc diff
		calcDiffImg();
		if (isDiffImgEmpty())
		{
			qDebug() << "Error in Frame Difference Calculation";
		}

		// write image to disk		
		QString targetPath = targetDir + "/" + QString::number(previous) + ".png";
		imwrite(targetPath.toStdString().data(), getDiffImg());
		imshow("show", getDiffImg());
		waitKey(30);
	}
}

bool FrameDifference::setPreviousImg(const char* nowPath)
{
	previousImg = imread(nowPath);
	if (previousImg.empty())
	{
		cout << "Read previous frame fail!" << endl;
		return false;
	}
	return true;
}

Mat FrameDifference::getPreviousImg()
{
	return previousImg;
}

bool FrameDifference::setNextImg(const char* nowPath)
{
	nextImg = imread(nowPath);
	if (nextImg.empty())
	{
		cout << "Read next frame fail!" << endl;
		return false;
	}
	return true;
}

Mat FrameDifference::getNextImg()
{
	return nextImg;
}

void FrameDifference::calcDiffImg()
{
	diffImg = getNextImg() - getPreviousImg();
}

Mat FrameDifference::getDiffImg()
{
	return diffImg;
}

bool  FrameDifference::isDiffImgEmpty(){
	if (diffImg.empty())
		return true;
	else
		return false;
}

void FrameDifference::setOrder(int num)
{
	order = num;
}

int FrameDifference::getOrder()
{
	return order;
}