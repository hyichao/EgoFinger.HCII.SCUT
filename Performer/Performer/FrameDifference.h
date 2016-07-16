#pragma once
#include "common.h"

class FrameDifference
{
public:
	FrameDifference();
	~FrameDifference();

public:
	// order setter and getter
	void setOrder(int num);
	int getOrder();

	void showFrameDifference(QString dir, QString txtPath, QString target);


private:
	//read and calculation image difference
	bool setPreviousImg(const char* path);
	Mat getPreviousImg();
	bool setNextImg(const char* path);
	Mat getNextImg();
	void calcDiffImg();
	Mat getDiffImg();
	bool isDiffImgEmpty();


private:
	Mat diffImg;				//Frame Difference Mat
	Mat previousImg, nextImg;	//previous and next mat
	int order;					//stage of difference
};

