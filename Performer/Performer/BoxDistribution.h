#pragma once
#include "common.h"
#include "Utils.h"

class BoxDistribution
{
public:
	BoxDistribution();
	~BoxDistribution();

public:

	void showFrequencyMat(string txtPath);

private:

	// to store counting number, CV_32SC1 type
	Mat countingMat;

	// to display frequency with uchar type£¨0-255£©
	Mat frequancyMat;

	
	void addUpCountingMat(double[]);

	void normalizeCountingMat(double[]);

	// init of two mats
	void initCountingMat();
	void initFrequencyMat();

};

