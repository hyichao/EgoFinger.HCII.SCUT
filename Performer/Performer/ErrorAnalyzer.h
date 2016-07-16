#pragma once
#include "common.h"
#include "Utils.h"

class ErrorAnalyzer
{
public:
	ErrorAnalyzer();
	~ErrorAnalyzer();

public:

	void setImageDir(string dir);
	void setTxtDir(string dir);

	void readImage(int index);
	void readLabels(int index);
	void showImageWithMultiPoints(int index);

	void calcAverage();
	void calcDiffAvg();
	void calcVariance();


private:

	string imageDir;
	string txtDir;

	Mat currentImage;
	double currentLabel[14][16];
	double avg[DEFAULT_COORD_NUM];
	double dif[DEFAULT_POINT_NUM];
	double var[DEFAULT_POINT_NUM];
};
