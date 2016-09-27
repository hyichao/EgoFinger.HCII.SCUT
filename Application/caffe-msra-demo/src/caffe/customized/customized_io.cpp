#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <algorithm>
#include <string>
#include <vector>

#include "caffe/common.hpp"
#include "caffe/util/io.hpp"

#include "caffe/customized/customized_io.hpp"

namespace caffe{

  // @Override to deal with multi-float label
  bool ReadImage2Datum(const string& filename, const std::vector<float> label,
      const int height, const int width, const bool is_color,
      const std::string & encoding, bool fast, Datum* datum) {
    cv::Mat cv_img = ReadImageToCVMat(filename, height, width, is_color);   
    if (cv_img.data) {
      
      CVMat2Datum(cv_img, datum, fast); 
      
      // add label
      for(int i=0; i<label.size(); i++)
          datum->add_float_label(label[i]);
      
      return true;

    } else {
      return false;
    }
  }

  //@New to support Datum to cvmat
  void Datum2CVMat(const Datum& datum, cv::Mat& cv_img) {
    
    int datum_channels = datum.channels();
    int datum_height = datum.height();
    int datum_width = datum.width();
    
    // LOG(INFO)<<"datum info (c,h,w): "<<datum_channels<<", "<<datum_height<<","<<datum_width;

    cv::Mat img(datum_height, datum_width, CV_8UC3);

    const string& buffer = datum.data();
    for (int h = 0; h < datum_height; ++h) {
      uchar* ptr = img.ptr<uchar>(h);
      int img_index = 0;
      for (int w = 0; w < datum_width; ++w) {
        for (int c = 0; c < datum_channels; ++c) {
          int datum_index = (c * datum_height + h) * datum_width + w;
          ptr[img_index++] = buffer[datum_index];
        }
      }
    }
    cv_img = img;
  }


  //@New to support Datum to cvmat
  void Datum2CVMat(const Datum& datum, cv::Mat& cv_img, bool fast) {
    
    if(!fast){
      Datum2CVMat(datum, cv_img);
      return;
    }

    int datum_channels = datum.channels();
    int datum_height = datum.height();
    int datum_width = datum.width();
    
    // LOG(INFO)<<"datum info (c,h,w): "<<datum_channels<<", "<<datum_height<<","<<datum_width;
    cv::Mat img(datum_height, datum_width, CV_8UC3);
    memcpy(img.data, datum.data().c_str(), datum_height*datum_width*datum_channels);

    cv_img = img;
  }


  //@Original in io.cpp
  void CVMat2Datum(const cv::Mat& cv_img, Datum* datum) {
    CHECK(cv_img.depth() == CV_8U) << "Image data type must be unsigned byte";
    datum->set_channels(cv_img.channels());
    datum->set_height(cv_img.rows);
    datum->set_width(cv_img.cols);
    datum->clear_data();
    datum->clear_float_data();
    datum->clear_float_label();//@New from proto message
    datum->set_encoded(false);
    int datum_channels = datum->channels();
    int datum_height = datum->height();
    int datum_width = datum->width();
    int datum_size = datum_channels * datum_height * datum_width;
    std::string buffer(datum_size, ' ');
    for (int h = 0; h < datum_height; ++h) {
      const uchar* ptr = cv_img.ptr<uchar>(h);
      int img_index = 0;
      for (int w = 0; w < datum_width; ++w) {
        for (int c = 0; c < datum_channels; ++c) {
          int datum_index = (c * datum_height + h) * datum_width + w;
          buffer[datum_index] = static_cast<char>(ptr[img_index++]);
        }
      }
    }
    datum->set_data(buffer);
  }


  void CVMat2Datum(const cv::Mat& cv_img, Datum* datum, bool fast) {

    if(!fast){
      CVMat2Datum(cv_img, datum);
      return;
    }

    CHECK(cv_img.depth() == CV_8U) << "Image data type must be unsigned byte";
    datum->set_channels(cv_img.channels());
    datum->set_height(cv_img.rows);
    datum->set_width(cv_img.cols);
    datum->clear_data();
    datum->clear_float_data();
    datum->clear_float_label();//@New from proto message
    datum->set_encoded(false);
    int datum_channels = datum->channels();
    int datum_height = datum->height();
    int datum_width = datum->width();
    int datum_size = datum_channels * datum_height * datum_width;
    
    std::string buffer(datum_size, ' ');
    const uchar* ptr = cv_img.data;
    for(int index = 0; index < datum_size; index++){
      buffer[index] = static_cast<char>(ptr[index]);
    }

    datum->set_data(buffer);
  }


  // @New just to display
  void displayCVMat(const cv::Mat cv_img, float* points,  int show_point_num){
    if(show_point_num==0){
      cv::imshow("show cv img without points", cv_img);
      cv::waitKey(0);
      return;
    }

    int rows = cv_img.rows;
    int cols = cv_img.cols;

    cv::Mat show_mat;
    cv_img.copyTo(show_mat);
    for(int i = 0 ; i < show_point_num; i++){
      LOG(ERROR)<<"NO."<<i<<": "<<points[2*i]<<" , "<<points[2*i+1];
      cv::circle(show_mat, cv::Point(points[2*i]*cols, points[2*i+1]*rows), 2, cv::Scalar(0,0,255), 2);
    }
    cv::imshow("show cv img with points", show_mat);
    cv::waitKey(0);
  }


  void displayDatumShape(const Datum datum)
  {
     LOG(INFO)<<"<Show Datum Shape> "
     <<" height: "<<datum.height()
     <<" width: "<<datum.width()
     <<" channels: "<<datum.channels()
     <<" float label size: "<<datum.float_label_size()
     ;
  }

} // namespace caffe