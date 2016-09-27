#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

#include "caffe/common.hpp"
#include "caffe/util/io.hpp"

#include "caffe/customized/customized_io.hpp"
#include "caffe/customized/customized_util.hpp"

using namespace std;

namespace caffe{

  //@New to support random crop
  bool Raw2FingerDummy(Datum& datum, int new_width, int new_height, int point_label_count){

    cv::Mat cv_img;
    Datum2CVMat(datum,cv_img,false);//not fast one
    if(!cv_img.data)
      return false;

    // get float label and de-normalized
    const int float_label_size = datum.float_label_size();
    float* float_label = new float[float_label_size];

    for(int label_id = 0; label_id < float_label_size; label_id++){
      float_label[label_id] = datum.float_label(label_id);
    }

    // displayCVMat(cv_img, float_label, 6);

    //crop with random enlargement
    const int rect_label_count = 4;
    float* rect_label = new float[rect_label_count];

    float* point_label = new float[point_label_count];

    cv::Mat roi;
    randomCrop(cv_img, roi, 
      float_label, float_label_size,
      rect_label, rect_label_count,
      point_label, point_label_count);

    // displayCVMat(roi, point_label, 4);

    // affine with random angle
    const int affine_label_count = point_label_count;
    float* affine_label = new float[affine_label_count];

    cv::Mat affine_roi;
    affineTransform(roi, affine_roi,
      point_label, point_label_count,
      affine_label, affine_label_count);

    // displayCVMat(affine_roi, affine_label, 4);

    resize(affine_roi, affine_roi, cv::Size(new_width, new_height));

    // displayCVMat(affine_roi, affine_label, 4);

    // write datum
    Datum* ptr_datum = &datum;
    CVMat2Datum(affine_roi, ptr_datum);// this method will clear some label data
    //recording label as well
    ptr_datum->clear_float_label();
    for(int i = 0; i < point_label_count; i++){
      ptr_datum->add_float_label(point_label[i]);
    }

    delete float_label;
    delete rect_label;
    delete point_label;
    delete affine_label;

    if(roi.data)
      return true;
    else
      return false;
  }

  // @New to support random crop, with image data layer input
  bool Raw2FingerDummy(const cv::Mat& src, cv::Mat& dst, 
    int new_width, int new_height,
    float* input_label, int input_label_size, 
    float* output_label, int output_label_size){

    if(!src.data) return false;

    // get float label and de-normalized
    const int float_label_size = input_label_size;
    float* float_label = new float[float_label_size];
    for(int index = 0; index < float_label_size; index+=2){
      float_label[index] = input_label[index];
      float_label[index+1] = input_label[index+1];
    }

    //crop with random enlargement
    const int rect_label_count = 4;
    float* rect_label = new float[rect_label_count];

    const int point_label_count = output_label_size;
    float* point_label = new float[point_label_count];

    cv::Mat roi;
    randomCrop(src, roi, 
      float_label, float_label_size,
      rect_label, rect_label_count,
      point_label, point_label_count);

    // affine with random angle
    const int affine_label_count = point_label_count;
    float* affine_label = new float[affine_label_count];

    cv::Mat affine_roi;
    affineTransform(roi, affine_roi,
      point_label, point_label_count,
      affine_label, affine_label_count);

    resize(affine_roi, affine_roi, cv::Size(new_width, new_height));

    // record label into output ptr
    for(int i = 0; i < point_label_count; i++){
      output_label[i] = point_label[i];
    }

    delete float_label;
    delete rect_label;
    delete point_label;
    delete affine_label;

    cv::imshow("pause and show", roi);
    cv::waitKey(0);

    if(roi.data)
      return true;
    else
      return false;
  }



  //@Private using
  void randomCrop(const cv::Mat& cv_img, cv::Mat& dst,
          float* float_label, int float_label_count, 
          float* rect_label, int rect_label_count,
          float* point_label, int point_label_count){

    const int padding_range = 20;
    const int mini_padding = 0;

    int width = cv_img.cols;
    int height = cv_img.rows;

    //enlarge bounding box, need protection, if out, stop enlargement at bounds
    rect_label[0] = float_label[0]*width - (rand()%padding_range)+mini_padding;
    rect_label[1] = float_label[1]*height - (rand()%padding_range)+mini_padding;
    rect_label[2] = float_label[2]*width + (rand()%padding_range)+mini_padding;
    rect_label[3] = float_label[3]*height + (rand()%padding_range)+mini_padding;
    if(rect_label[0] < 0) rect_label[0] = 0;
    if(rect_label[1] < 0) rect_label[1] = 0;
    if(rect_label[2] > cv_img.cols) rect_label[2] = width;
    if(rect_label[3] > cv_img.rows) rect_label[3] = height;

    float rectWidth = rect_label[2] - rect_label[0];
    float rectHeight = rect_label[3] - rect_label[1];

    //make roi
    cv::Mat roi(cv_img,cv::Rect(rect_label[0], rect_label[1], rectWidth, rectHeight));

    // convert calculation
    for(int i=0; i<point_label_count; i+=2){
      point_label[i] = (float_label[i+4]*width - rect_label[0])/rectWidth;
      point_label[i+1] = (float_label[i+1+4]*height - rect_label[1])/rectHeight;

      if(float_label[i+4]==0) point_label[i]=0;
      if(float_label[i+1+4]==0) point_label[i+1]=0;
    }

    //convert cvmat to datum
    dst=roi;
  }

  //@Private using
  void affineTransform(cv::Mat& src, cv::Mat& dst, 
    float* point_label, int point_label_count,
    float* affine_label, int affine_label_count) {
    
    cv::Mat rot_mat(2, 3, CV_32FC1);
    dst = cv::Mat::zeros(src.rows, src.cols, src.type());

    /** Rotating the image after Warp */
    /// Compute a rotation matrix with respect to the center of the image
    int offsetX = rand()%50-25;
    int offsetY = rand()%50-25;
    
    cv::Point center = cv::Point(dst.cols/2+offsetX, dst.rows/2+offsetY);
    double scale = 1;
    double angle = rand()%180-90;

    /// Get the rotation matrix with the specifications above
    rot_mat = cv::getRotationMatrix2D(center, angle, scale);
    double a11 = rot_mat.at<double>(0,0);
    double a12 = rot_mat.at<double>(0,1);
    double a21 = rot_mat.at<double>(1,0);
    double a22 = rot_mat.at<double>(1,1);
    double b11 = rot_mat.at<double>(0,2);
    double b12 = rot_mat.at<double>(1,2);

    //if points get out of bounding box, keep everythin the same and return
    bool keep_same = false;
    for(int i = 0; i < point_label_count; i+=2){
      float label_x = point_label[i]*src.cols;
      float label_y = point_label[i+1]*src.rows;

      float new_label_x = (label_x*a11+label_y*a12+b11)/src.cols;
      float new_label_y = (label_x*a21+label_y*a22+b12)/src.rows;

      if(new_label_x<0 || new_label_x>1 || new_label_y<0 || new_label_y>1) {
        keep_same = true;
      }

      affine_label[i] = new_label_x;
      affine_label[i+1] = new_label_y;

      if(point_label[i]==0) affine_label[i]=0;
      if(point_label[i+1]==0) affine_label[i+1]=0;
    }

    if(keep_same){
      src.copyTo(dst);
      for(int i = 0; i < affine_label_count; i++){
        affine_label[i] = point_label[i];
      }
    } else{
      // Rotate the warped image
      cv::warpAffine(src, dst, rot_mat, dst.size(), 
        cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(122,122,122));
    }
  }

  /**
  * The following is for infinite dummy hand
  */

  // @New to make hand dummy with translation
  bool Raw2HandDummy(Datum& datum){

    cv::Mat cv_img;
    Datum2CVMat(datum,cv_img,true);
    if(!cv_img.data)
      return false;

    int height = cv_img.rows;
    int width = cv_img.cols;
    // LOG(INFO)<<"Converted rows and cols: "<<height<<","<<width;

    // get float label and de-normalized
    const int float_label_size = datum.float_label_size();
    float* float_label = new float[float_label_size];

    for(int label_id = 0; label_id < float_label_size; label_id+=2){
      float_label[label_id] = datum.float_label(label_id)*width;
      float_label[label_id+1] = datum.float_label(label_id+1)*height;
    }

    //translate
    const int rect_label_count = 4;
    float* rect_label = new float[rect_label_count];

    cv::Mat dst;
    translate(cv_img, dst, float_label, float_label_size, rect_label, rect_label_count);

    // write datum
    Datum* ptr_datum = &datum;
    CVMat2Datum(dst, ptr_datum);// this method will clear some label data
    //recording label as well
    ptr_datum->clear_float_label();
    for(int i = 0; i < rect_label_count; i++){
      ptr_datum->add_float_label(rect_label[i]);
    }

    delete float_label;
    delete rect_label;

    if(dst.data)
      return true;
    else
      return false;

  }

  // @New translate with random direction and random offset
  void translate(cv::Mat& src, cv::Mat& dst, 
    float* old_label, int old_label_size, float* new_label, int new_label_size){

    cv::Mat rot_mat(2, 3, CV_32FC1);
    dst = cv::Mat::zeros(src.rows, src.cols, src.type());

    /** Rotating the image after Warp */
    /// Compute a rotation matrix with respect to the center of the image
    int offsetX = 50;
    int offsetY = 0;
    

    rot_mat.at<double>(0,0) = 0;
    rot_mat.at<double>(0,1) = 0;
    rot_mat.at<double>(1,0) = 0;
    rot_mat.at<double>(1,1) = 0;
    rot_mat.at<double>(0,2) = offsetX;
    rot_mat.at<double>(1,2) = offsetY;

    // Rotate the warped image
    cv::warpAffine(src, dst, rot_mat, dst.size(), 
      cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(122,122,122));

    double a11 = rot_mat.at<double>(0,0) < 0.0001? 0:rot_mat.at<double>(0,0);
    double a12 = rot_mat.at<double>(0,1) < 0.0001? 0:rot_mat.at<double>(0,1);
    double a21 = rot_mat.at<double>(1,0) < 0.0001? 0:rot_mat.at<double>(1,0);
    double a22 = rot_mat.at<double>(1,1) < 0.0001? 0:rot_mat.at<double>(1,1);
    double b11 = rot_mat.at<double>(0,2) < 0.0001? 0:rot_mat.at<double>(0,2);
    double b12 = rot_mat.at<double>(1,2) < 0.0001? 0:rot_mat.at<double>(1,2);

    for(int i = 0; i < new_label_size; i+=2){
      float label_x = old_label[i]*src.cols;
      float label_y = old_label[i+1]*src.rows;

      float new_label_x = (label_x*a11+label_y*a12+b11)/src.cols;
      float new_label_y = (label_y*a21+label_y*a22+b12)/src.rows;

      new_label[i] = new_label_x;
      new_label[i+1] = new_label_y;
    }
  }

  // void AffineCrop(const cv::Mat& src, const vector<cv::Point>& box_points, const float angle,
  //             cv::Mat& affine_crop_mat, cv::Mat& affine_mat){ 
  // TODO: figure out why "const reference doesn't work"
  void AffineCrop(cv::Mat& src, vector<cv::Point>& box_points, float angle,
              cv::Mat& affine_crop_mat, cv::Mat& affine_mat){
    // rotation parameter
    cv::Point center((box_points[0].x+box_points[1].x)/2, (box_points[0].y+box_points[1].y)/2);
    float rotate = 90-angle; // anti-clockwise 
    float scale = 1;
    // rotation
    cv::Mat transform_mat(2, 3, CV_32FC1);  //旋转矩阵
    transform_mat = getRotationMatrix2D(center, rotate, scale);
    cv::Mat affine_src = cv::Mat::zeros(src.rows, src.cols, src.type());
    warpAffine(src, affine_src, transform_mat, affine_src.size(), 
               cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(127, 127, 127));
    
    // label transform
    // 4 points in src (clockwise)
    vector<cv::Point> points(4); 
    points[0] = cv::Point(box_points[0].x, box_points[0].y);
    points[1] = cv::Point(box_points[1].x, box_points[0].y);
    points[2] = cv::Point(box_points[1].x, box_points[1].y);
    points[3] = cv::Point(box_points[0].x, box_points[1].y);
    // label in rotated src
    vector<cv::Point> rot_points(points.size()); 
    for(int i=0; i<points.size(); i++){
      rotate_point(src, points[i], transform_mat, rot_points[i]);
    }

    // new bounding box in rotated src
    cv::Rect crop_rect;
    get_bounding_box(rot_points, crop_rect);

    // show points in rotated src
    cv::Mat affineCopy = affine_src.clone();
    for(int i=0; i<rot_points.size(); i++){
      cv::line(affineCopy, rot_points[i], rot_points[(i+1)%rot_points.size()], cv::Scalar(0,0,255), 3);
      cv::rectangle(affineCopy, crop_rect, cv::Scalar(0,255,0), 3);
    }

    // Adapt the rect ratio
    cv::Rect rect_to_compute_area(box_points[0], box_points[1]);
    AdaptBoxRatio(src, 1.5, rect_to_compute_area, crop_rect, crop_rect);
    // AdaptBoxRatio(src, 1.5, crop_rect, crop_rect, crop_rect);
    // AdaptBoxRatio(src, 1.64, rect_to_compute_area, crop_rect, crop_rect);
    // AdaptBoxRatio(src, 1.64, crop_rect, crop_rect, crop_rect);

    // show
    cv::rectangle(affineCopy, crop_rect, cv::Scalar(255,0,0), 3);

    cv::imshow("rotated mat", affineCopy);

    // crop    
    affine_crop_mat = affine_src(crop_rect);
    affine_mat = transform_mat;

    // show crop_rect in src
    cv::Mat srcCopy = src.clone();
    cv::Size size(crop_rect.width, crop_rect.height);
    cv::RotatedRect crop_rect_in_src(center, size, rotate);
    cv::Point2f vertices[4];
    crop_rect_in_src.points(vertices);
    for (int i = 0; i < 4; ++i)
    {
      cv::line(src, vertices[i], vertices[(i+1)%4], cv::Scalar(0,0,255),3);
    }
    // cv::imshow("rotated crop in src", srcCopy);

  }

  void rotate_point(const cv::Mat& src, const cv::Point& in_point, const cv::Mat& rot_mat, cv::Point& out_point){
    double a11 = rot_mat.at<double>(0,0);
    double a12 = rot_mat.at<double>(0,1);
    double a21 = rot_mat.at<double>(1,0);
    double a22 = rot_mat.at<double>(1,1);
    double b11 = rot_mat.at<double>(0,2);
    double b12 = rot_mat.at<double>(1,2);
    // rotate points
    out_point.x = (in_point.x*a11+in_point.y*a12+b11);
    out_point.y = (in_point.x*a21+in_point.y*a22+b12);
    // make sure in the image region
    out_point.x = min<float>(src.cols, out_point.x);
    out_point.x = max<float>(0, out_point.x);
    out_point.y = min<float>(src.rows, out_point.y);
    out_point.y = max<float>(0, out_point.y);
  }

  // void anti_rotate_point(const cv::Mat& src, const cv::Point& in_point, 
  //                        const cv::Point center, const float angle, 
  //                        cv::Point& out_point){
  //   double a11 = rot_mat.at<double>(0,0);
  //   double a12 = rot_mat.at<double>(0,1);
  //   double a21 = rot_mat.at<double>(1,0);
  //   double a22 = rot_mat.at<double>(1,1);
  //   double b11 = rot_mat.at<double>(0,2);
  //   double b12 = rot_mat.at<double>(1,2);
  //   a12 = -a12;
  //   a21 = -a21;
  //   // rotate points
  //   out_point.x = (in_point.x*a11+in_point.y*a12+b11);
  //   out_point.y = (in_point.x*a21+in_point.y*a22+b12);
  //   // make sure in the image region
  //   out_point.x = min<float>(src.cols-1, out_point.x);
  //   out_point.x = max<float>(0, out_point.x);
  //   out_point.y = min<float>(src.rows-1, out_point.y);
  //   out_point.y = max<float>(0, out_point.y);
  // }

  void get_bounding_box(const vector<cv::Point>& rot_points, cv::Rect& box_rect){
    CHECK_EQ(rot_points.size(), 4);
    vector<cv::Point> new_box_points(2);
    new_box_points[0].x = min<float>(min<float>(rot_points[0].x, rot_points[1].x), 
                                     min<float>(rot_points[2].x, rot_points[3].x));
    new_box_points[0].y = min<float>(min<float>(rot_points[0].y, rot_points[1].y), 
                                     min<float>(rot_points[2].y, rot_points[3].y));
    new_box_points[1].x = max<float>(max<float>(rot_points[0].x, rot_points[1].x), 
                                     max<float>(rot_points[2].x, rot_points[3].x));
    new_box_points[1].y = max<float>(max<float>(rot_points[0].y, rot_points[1].y), 
                                     max<float>(rot_points[2].y, rot_points[3].y));
    box_rect = cv::Rect(new_box_points[0], new_box_points[1]);
  }

  // void AdaptBoxRatio(const cv::Mat& src, const float ratio, cv::Rect& box, cv::Rect& adpat_box){
  //   float width  = box.width;
  //   float height = box.height;
  //   float center_x = box.x+width/2;
  //   float center_y = box.y+height/2;
    
  //   float area = height*width;
  //   float new_width = sqrt(area/ratio);
  //   float new_height = ratio*new_width; 
  //   adpat_box.x = center_x - new_width/2;
  //   adpat_box.y = center_y - new_height/2;
  //   adpat_box.width = new_width;
  //   adpat_box.height = new_height;

  //   // protect
  //   adpat_box.x = min<float>(src.cols-1, adpat_box.x);
  //   adpat_box.x = max<float>(0, adpat_box.x);
  //   adpat_box.y = min<float>(src.rows-1, adpat_box.y);
  //   adpat_box.y = max<float>(0, adpat_box.y);

  //   adpat_box.width = min<float>(src.cols-1-adpat_box.x, adpat_box.width);
  //   adpat_box.width = max<float>(0, adpat_box.width);
  //   adpat_box.height = min<float>(src.rows-1-adpat_box.y, adpat_box.height);
  //   adpat_box.height = max<float>(0, adpat_box.height);
  // }

  void AdaptBoxRatio(const cv::Mat& src, const float ratio, 
                     cv::Rect& rect_to_compute_area, cv::Rect& box, cv::Rect& adpat_box){
    //compute area
    float width  = rect_to_compute_area.width;
    float height = rect_to_compute_area.height;
    float area = width*height;

    //compute center
    float center_x = box.x+box.width/2;
    float center_y = box.y+box.height/2;
    
    // adapt ratio

    float new_width = sqrt(area/ratio);
    float new_height = ratio*new_width;
    
    // check center
    // cv::Mat srcCopy = src.clone();
    // cv::circle(srcCopy, cv::Point(center_x, center_y), 3, cv::Scalar(0,0,255), 3);
    // cv::imshow("check center", srcCopy);

    adpat_box.x = center_x - new_width/2;
    adpat_box.y = center_y - new_height/2;
    adpat_box.width = new_width;
    adpat_box.height = new_height;

    // protect
    adpat_box.x = min<float>(src.cols-1, adpat_box.x);
    adpat_box.x = max<float>(0, adpat_box.x);
    adpat_box.y = min<float>(src.rows-1, adpat_box.y);
    adpat_box.y = max<float>(0, adpat_box.y);

    adpat_box.width = min<float>(src.cols-1-adpat_box.x, adpat_box.width);
    adpat_box.width = max<float>(0, adpat_box.width);
    adpat_box.height = min<float>(src.rows-1-adpat_box.y, adpat_box.height);
    adpat_box.height = max<float>(0, adpat_box.height);
  }

  void DrawPoints(cv::Mat& src, string windowName, vector<cv::Point>& points, cv::Scalar scalar){
    for(int i=0; i<points.size(); i++)
      cv::circle(src, points[i], 3, scalar, 3);
    cv::imshow(windowName, src);
  }

  void offset_rect(cv::Rect& in_rect, cv::Rect& out_rect, cv::Point track_center, cv::Size original_size){
    out_rect.x = track_center.x-original_size.width/2+in_rect.x;
    out_rect.y = track_center.y-original_size.height/2+in_rect.y;
  }

  void offset_points(vector<cv::Point>& in_points, vector<cv::Point>& out_points, cv::Point track_center, cv::Size original_size){
  for (int i = 0; i < in_points.size(); ++i)
    {
      out_points[i].x = track_center.x-original_size.width/2+in_points[i].x;
      out_points[i].y = track_center.y-original_size.height/2+in_points[i].y;
    }
  }
  void offset_point(cv::Point& in_point, cv::Point& out_point, cv::Point track_center, cv::Size original_size){
    out_point.x = track_center.x-original_size.width/2+in_point.x;
    out_point.y = track_center.y-original_size.height/2+in_point.y;
  }

  void protect_rect_edge(const cv::Mat src, cv::Rect& rect){
    rect.x = min<float>(src.cols-1, rect.x);
    rect.x = max<float>(0, rect.x);
    rect.y = min<float>(src.rows-1, rect.y);
    rect.y = max<float>(0, rect.y);

    rect.width = min<float>(src.cols-1-rect.x, rect.width);
    rect.width = max<float>(0, rect.width);
    rect.height = min<float>(src.rows-1-rect.y, rect.height);
    rect.height = max<float>(0, rect.height);

  }

  void protect_point_edge(const cv::Mat src, vector<cv::Point>& points){
    for (int i = 0; i < points.size(); ++i)
    {
      points[i].x = min<float>(src.cols-1, points[i].x);
      points[i].x = max<float>(0, points[i].x);
      points[i].y = min<float>(src.rows-1, points[i].y);
      points[i].y = max<float>(0, points[i].y);
    }
  }

  void protect_point_edge(const cv::Mat src, cv::Point& point){
      point.x = min<float>(src.cols-1, point.x);
      point.x = max<float>(0, point.x);
      point.y = min<float>(src.rows-1, point.y);
      point.y = max<float>(0, point.y);
  }


} // namespace caffe