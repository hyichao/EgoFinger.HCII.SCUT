#pragma once
#include "common.h"
class Utils
{
public:
	Utils();
	~Utils();

public:
	
	// using this method to draw mat with hist input, while hist should be float element
	void static drawHistImageByHistMat(Mat hist, int scale, int binHeight, int binNum, string name);

	// using this method to write mat into txt, while hist should be float element
	void static writeHistMatIntoTxt(Mat hist,string targetPath, string uuid);

	// find out max in a mat
	static int findOutMaxIn32BitMat(Mat mat);
	static int findOutMaxIn8BitMat(Mat mat);

	// calc average
	static double calcAverage(double data[], int num);

	static string stringFromInt(int num);

	static double calcDistance(int x1, int y1, int x2, int y2);

	static Mat calcHistogram(const Mat &image);
};

