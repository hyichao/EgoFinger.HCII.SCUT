#pragma once
#include "common.h"
#include "Utils.h"

enum PointType
{
	BOUNDING_BOX_TOP_LEFT = 0,
	BOUNDING_BOX_BOTTOM_RIGHT,
	INDEX_FINGERTIP,
	INDEX_JOINT,
	TAIL_JOINT,
	THUMB_TIP,
	THUMB_JOINT,
};

class MovementDetector
{
public:
	MovementDetector();
	~MovementDetector();

public:
	void setTxtPath(string txtPath);
	void showMovementHistogram(PointType type);

	void setTxtOutPath(string txtPath);
	void writeMovementIntoTxt(string path);

private:

	string txtInPath;
	string txtOutPath;

	Mat movementMat[7];

	void processTxtContent();
	void initMovementMat();
	void recordInfoIntoMat(double movement[]);
	
};

