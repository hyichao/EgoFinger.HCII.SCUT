#ifndef CAFFE_CUSTOMIZED_WRITING_H_
#define CAFFE_CUSTOMIZED_WRITING_H_

#include <string>
#include <vector>
#include <opencv2/opencv.hpp> //*****
#include <math.h> // for sqrt()

#include "caffe/common.hpp"//like LOG

#include "iRecognize.h" // for writing recognition

using namespace cv;
using namespace std;


class WritingTool{

public:
	void init();
	void expire();
	void addPoint(cv::Point sPoint);
	void clearPoints();
	int getPointCount();
	vector<cv::Point> getPoints();

    cv::Mat showPointsOnMat(const cv::Mat& src, bool show);

	string recognizeCharacter();

	static void UnicodeToUTF8(char* pOut,char* pIn){
	    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	    pOut[0] = (0xE0 | ((pIn[0] & 0xF0) >> 4));
	    pOut[1] = (0x80 | ((pIn[0] & 0x0F) << 2)) + ((pIn[1] & 0xC0) >> 6);
	    pOut[2] = (0x80 | (pIn[1] & 0x3F));
	    return;
	}
private:
	vector<cv::Point> points_;
	// cv::VideoWriter writer;

private:
	void smoothPoints();
};

#endif   // CAFFE_CUSTOMIZED_WRITING_H_
