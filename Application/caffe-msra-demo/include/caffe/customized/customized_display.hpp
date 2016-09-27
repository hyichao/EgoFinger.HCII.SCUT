#ifndef CAFFE_CUSTOMIZED_DISPLAY_H_
#define CAFFE_CUSTOMIZED_DISPLAY_H_

#include <unistd.h>
#include <stdio.h>  // for snprintf
#include <string>
#include <vector>
#include <opencv2/opencv.hpp> //*****
#include <math.h> // for sqrt()
#include <time.h>
#include <ctime>

#include "caffe/common.hpp"//like LOG
#include "caffe/customized/customized_display.hpp"

using std::string;
using namespace cv;
using namespace std;

class CTimer{

public:
	CTimer(){
		start=clock();
	}

	void setStart(){
		start=clock();
	}
	void calcDiff(){
		end=clock();
		diff=float(end-start)/1000;
		// LOG(ERROR)<<"Time Consumption: "<<diff<<";";
	}
	float getDiff(){
		calcDiff();
		return diff;
	}

private:
	clock_t start;
	clock_t end;
	float diff;
};


#define WAITTIME (10)

class DisplayTool{

public:
	static void ConvertGroundTruth(const vector<pair<string, vector<float> > >& lines,
		int img_width, int img_height, vector<vector<float> >& gt_coords);
	static void EnlargeBoundingBox(const vector<cv::Point>& box_coords,
	    vector<cv::Point>& larger_box_coords);

	static cv::Mat DisplayBoundingBox(cv::Mat src, string mode, string windowName,
		cv::Point pre_tl, cv::Point pre_br, cv::Point gt_tl, cv::Point gt_br);
	static cv::Mat DisplayBoundingBoxWithCenter(cv::Mat src, string mode, string windowName,
		cv::Point pre_tl, cv::Point pre_br, cv::Point gt_tl, cv::Point gt_br);
	static cv::Mat DisplayFingerPoints(cv::Mat src, string mode,
		cv::Point pre_ft, cv::Point pre_jnt, cv::Point gt_ft, cv::Point gt_jnt);
	static cv::Mat DisplayPoints(cv::Mat src, string mode,
		cv::Point pre_tl, cv::Point pre_br, cv::Point gt_tl, cv::Point gt_br,
		cv::Point pre_ft, cv::Point pre_jnt, cv::Point gt_ft, cv::Point gt_jnt);

	static void CutROI(const cv::Mat& src, cv::Mat& dst, cv::Point pre_tl, cv::Point pre_br);
};

#endif   // CAFFE_CUSTOMIZED_DISPLAY_H_
