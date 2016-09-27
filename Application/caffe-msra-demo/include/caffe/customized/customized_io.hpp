#ifndef CAFFE_UTIL_M_IO_H_
#define CAFFE_UTIL_M_IO_H_

#include <unistd.h>
#include <vector>
#include <string>

#include "caffe/common.hpp"

namespace caffe {

	/**
	customer io
	*/

	// convert mat into datum, normal method and fast customized method
	void CVMat2Datum(const cv::Mat& cv_img, Datum* datum);
	void CVMat2Datum(const cv::Mat& cv_img, Datum* datum, bool fast);

	//to convert datum back to mat, normal method and fast customized method
	void Datum2CVMat(const Datum& datum, cv::Mat& cv_img);
	void Datum2CVMat(const Datum& datum, cv::Mat& cv_img, bool fast);

	//to support multi label
	bool ReadImage2Datum(const string& filename, const std::vector<float> labels, 
			const int height, const int width, const bool is_color,
			const std::string & encoding, bool fast, Datum* datum);

	/**
	customer display
	*/

	// to display mat
  	void displayCVMat(const cv::Mat cv_img, float* points, int show_point_num=0);

  	// to show datum shape
  	void displayDatumShape(const Datum datum);

}  // namespace caffe

#endif   // CAFFE_UTIL_M_IO_H_
