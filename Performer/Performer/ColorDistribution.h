#pragma once
#include "common.h"
#include "Utils.h"

enum DistributionType
{
	WHOLE_IMAGE = 0,
	INSIDE_BOUNDING_BOX ,
	OUTSIDE_BOUNDING_BOX,
	
};

enum ColorSpace
{
	SPACE_BGR = 0,
	SPACE_HSV,
	SPACE_YCrCb,
	SPACE_Lab,
};

class ColorDistribution
{
public:

	ColorDistribution();
	~ColorDistribution();

	void init(string dirPath, string inPath, DistributionType type, ColorSpace colorSpace);
	void calcHistogram();
	void showHistogram();


private:
	string imageDir;								// the folder directory of images
	string inputTxtPath;							// input txt file
	DistributionType type;
	ColorSpace colorSpace;

	Mat histX, histY, histZ;						// record hist (X,Y,Z for corresponding channel)
	
	string pictureName;
	double boxCoord[4];								//boxLeftX, boxLeftY, boxRightX, boxRightY;
	double pointCoord[10];							//indexX, indexY, inJointX, inJointY, littleJointX, littleJointY, thumbX, thumbY, thumbJointX, thumbJointY;

private:

	Mat readImage(string imageName);

	// calculation
	void addUpHist();
};

