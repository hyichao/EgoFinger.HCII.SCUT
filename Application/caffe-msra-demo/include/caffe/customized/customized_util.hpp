#ifndef CAFFE_UTIL_CUSTOMIZED_H_
#define CAFFE_UTIL_CUSTOMIZED_H_

#include <unistd.h>
#include <vector>
#include <string>

#include "caffe/blob.hpp"
#include "caffe/common.hpp"

#include "caffe/customized/customized_io.hpp"

namespace caffe {

	/**
	customer dummy finger transformation
	*/

	//to make infinite dummy data with lmdb input, which convert from datum
	bool Raw2FingerDummy(Datum& datum, 
			int new_width, int new_height, int point_label_count);
	bool Raw2FingerDummy(const cv::Mat& src, cv::Mat& dst,
			int new_width, int new_height, 
			float* input_label, int input_label_size, 
			float* output_label, int output_label_size);

	// for private using 
	void randomCrop(const cv::Mat& cv_img, cv::Mat& roi,
          float* float_label, int float_label_count, 
          float* rect_label, int rect_label_count,
          float* req_label, int req_label_count);
	void affineTransform(cv::Mat& src, cv::Mat& dst, 
	    float* req_label, int req_label_count,
	    float* affine_label, int affine_label_count);

	/**
	customer dummy hand transformation
	*/
	bool Raw2HandDummy(Datum& datum);

	void translate(cv::Mat& src, cv::Mat& dst, 
		float* old_label, int old_label_size, float* new_label, int new_label_size);
	/** 
	 * Input: src, lt rb point, angle
	 * Output: affine_crop_roi(旋转后的外接crop区域), affine_mat(仿射变换矩阵) 
	 **/
	void AffineCrop(cv::Mat& src, vector<cv::Point>& box_points, float angle,
              cv::Mat& affine_crop_mat, cv::Mat& affine_mat);
	// void AffineCrop(const cv::Mat& src, const vector<cv::Point>& box_points, const float angle,
 //              cv::Mat& affine_crop_mat, cv::Mat& affine_mat);
	void rotate_point(const cv::Mat& src, const cv::Point& in_point, const cv::Mat& rot_mat, cv::Point& out_point);
  	// void anti_rotate_point(const cv::Mat& src, const cv::Point& in_point, 
   //                         const cv::Point center, const float angle, 
   //                         cv::Point& out_point)
  	void get_bounding_box(const vector<cv::Point>& rot_points, cv::Rect& box_rect);
	void AdaptBoxRatio(const cv::Mat& src, const float ratio, 
		cv::Rect& rect_to_compute_area, cv::Rect& box, cv::Rect& adpat_box);
	void DrawPoints(cv::Mat& src, string windowName,
				    vector<cv::Point>& points, cv::Scalar scalar = cv::Scalar(0,0,255));
	void offset_rect(cv::Rect& in_rect, cv::Rect& out_rect, cv::Point track_center, cv::Size original_size);
	void offset_points(vector<cv::Point>& in_points, vector<cv::Point>& out_points, cv::Point track_center, cv::Size original_size);
	void offset_point(cv::Point& in_point, cv::Point& out_point, cv::Point track_center, cv::Size original_size);

	// void offset(cv::Rect& rect, int offset_x, int offset_y);
	// void offset(vector<cv::Point>& points, int offset_x, int offset_y);
	// void track_update(cv::Rect rect, cv::Point& center);
	// void track_update(vector<cv::Point> points, cv::Point& center);

	void protect_rect_edge(const cv::Mat src, cv::Rect& rect);
	void protect_point_edge(const cv::Mat src, cv::Point& point);
	void protect_point_edge(const cv::Mat src, vector<cv::Point>& points);
}  // namespace caffe

#endif   // CAFFE_UTIL_CUSTOMIZED_H_
