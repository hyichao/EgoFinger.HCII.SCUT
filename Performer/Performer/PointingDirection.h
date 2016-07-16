#pragma once
#include "common.h"
#include "Utils.h"

class PointingDirection
{
public:
	PointingDirection();
	~PointingDirection();

	void setPath(string txtPath);
	void displayHistogram();

private:
	Mat hist;
	string path;

	void initHistMat();
	void analyzeDirection(string path);

};

