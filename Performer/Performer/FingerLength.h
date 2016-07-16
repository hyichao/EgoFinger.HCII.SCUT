#pragma once
#include "common.h"
#include "Utils.h"

class FingerLength
{
public:
	FingerLength();
	~FingerLength();

	void setPath(string txtPath);
	void displayHistogram();

private:
	Mat hist;
	string path;

	void initHistMat();
	void analyzeLength(string path);

};

