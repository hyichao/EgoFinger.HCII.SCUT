#include "ErrorAnalyzer.h"


ErrorAnalyzer::ErrorAnalyzer()
{
}


ErrorAnalyzer::~ErrorAnalyzer()
{
}

void ErrorAnalyzer::setImageDir(string dir)
{
	imageDir = dir;
}

void ErrorAnalyzer::setTxtDir(string dir)
{
	txtDir = dir;
}


void ErrorAnalyzer::readImage(int index)
{
	string imagePath = imageDir + "/HCIILab_color_" + Utils::stringFromInt(index) + ".png";
	currentImage = imread(imagePath);
}


void ErrorAnalyzer::readLabels(int index)
{
	for (int i = 0; i < 14; i++)
	for (int j = 0; j < 16; j++)
	{
		currentLabel[i][j] = -1;
	}

	for (int i = 0; i < 16; i++)
	{
		string txtPath = txtDir + "/label" + Utils::stringFromInt(i) + ".txt";
		ifstream infile(txtPath.c_str(), ios::in);
		if (!infile) abort();

		string fileName;
		double data[14];
		while (infile >> fileName >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5] >> data[6]
			>> data[7] >> data[8] >> data[9] >> data[10] >> data[11] >> data[12] >> data[13])
		{
			int start = 13;
			int end = fileName.find(".png");
			string subStr = fileName.substr(start, end);
			int fileNum = atoi(subStr.data());

			if (fileNum != index)
				continue;

			for (int j = 0; j < 14; j += 2)
				currentLabel[j][i] = data[j] * IMAGE_DEFAULT_WIDTH;
			for (int j = 1; j < 14; j+=2)
				currentLabel[j][i] = data[j] * IMAGE_DEFAULT_HEIGHT;
			break;
		}
	}
}

void ErrorAnalyzer::showImageWithMultiPoints(int index)
{
	readImage(index);
	readLabels(index);

	for (int i = 0; i < 14; i+=2)
	for (int j = 0; j < 16; j++)
	{
		Point center(currentLabel[i][j], currentLabel[i+1][j]);
		circle(currentImage, center, 3, Scalar(0, 0, 255), 2);
	}

	imshow("Image", currentImage);
	calcAverage();
	calcDiffAvg();
	calcVariance();
}

void ErrorAnalyzer::calcAverage()
{
	for (int i = 0; i < 14; i++)
	{
		int counter = 0;
		int sum = 0;
		for (int j = 0; j < 16; j++)
		{
			if (currentLabel[i][j] == -1)
				continue;

			sum += currentLabel[i][j];
			counter++;
		}

		avg[i] = sum * 1.0 / counter;
	}
	qDebug() << "center";
	for (int j = 0; j < 14; j+=2){
		qDebug() << "(" << avg[j] << "," << avg[j + 1] << ")";
	}
}

void ErrorAnalyzer::calcDiffAvg()
{
	for (int i = 0; i < 14; i+=2)
	{
		int counter = 0;
		int sum = 0;
		for (int j = 0; j < 16; j++)
		{
			if (currentLabel[i][j] == -1)
				continue;

			double xDiff = currentLabel[i][j] - avg[i];
			double yDiff = currentLabel[i + 1][j] - avg[i+1];
			double euclidean = (xDiff*xDiff + yDiff*yDiff);
			//qDebug() << sqrt(euclidean);
			sum += sqrt(euclidean);
			counter++;
		}
		dif[i/2] = sum * 1.0 / counter;
	}

	qDebug() << "Error Average";
	for (int j = 0; j < 7; j++){
		qDebug() << "No." << j << ": " << dif[j];
	}
}


void ErrorAnalyzer::calcVariance()
{
	for (int i = 0; i < 14; i+=2)
	{
		int counter = 0;
		int sum = 0;
		for (int j = 0; j < 16; j++)
		{
			if (currentLabel[i][j] == -1)
				continue;

			double xDiff = currentLabel[i][j] - avg[i];
			double yDiff = currentLabel[i + 1][j] - avg[i + 1];
			double euclidean = xDiff*xDiff + yDiff*yDiff;

			double diff = sqrt(euclidean) - dif[i / 2];
			sum += pow(diff, 2);
			counter++;
		}
		var[i/2] = sum * 1.0 / counter;
	}

	qDebug() << "Error Variance";
	for (int j = 0; j < 7; j++){
		qDebug() << "No." << j << ": " << var[j];
	}
}