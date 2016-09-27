#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "common.h"

/**
convertion of cvMat to blob
*/
template<typename Dtype>
vector<int> createBlobShape(int num, int channel, int height, int width)
{
    vector<int> shape(4,0);
    shape[0]=num;
    shape[1]=channel;
    shape[2]=height;
    shape[3]=width;
    return shape;
}

// override
template<typename Dtype>
void CvMats2blobVec(const vector<cv::Mat>& srcs, vector<Blob<Dtype>* >& transformed_blob_vec)
{
  // get size
  const int num = transformed_blob_vec[0]->num();
  const int channel  = transformed_blob_vec[0]->channels();
  const int height = transformed_blob_vec[0]->height();
  const int width  = transformed_blob_vec[0]->width();
  CHECK_EQ(num, srcs.size());

  // mean value
  vector<Dtype> mean_values(3,127);
  Dtype* transformed_data = transformed_blob_vec[0]->mutable_cpu_data();
  for(int n=0; n<num; n++){
    // resize
    cv::Mat cv_img;
    cv::resize(srcs[n], cv_img, cv::Size(width, height));
    // transform into blob
    int num_offset = transformed_blob_vec[0]->offset(n, 0, 0, 0);
    int top_index;
    for (int h = 0; h < height; ++h) {
      const uchar* ptr = cv_img.ptr<uchar>(h);
      int img_index = 0;
      for (int w = 0; w < width; ++w) {
        for (int c = 0; c < channel; ++c) {
            top_index = (c * height + h) * width + w;
            Dtype pixel = static_cast<Dtype>(ptr[img_index++]);
            transformed_data[num_offset+top_index] = (pixel - mean_values[c]);
        }
      }
    }
  }
}

#endif // TRANSFORM_H

