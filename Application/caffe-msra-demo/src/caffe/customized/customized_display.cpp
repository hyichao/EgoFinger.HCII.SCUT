#include "caffe/customized/customized_display.hpp"  

void DisplayTool::ConvertGroundTruth(const vector<pair<string, vector<float> > >& lines,
  int img_width, int img_height, vector<vector<float> >& gt_coords)
{
  int line_size = lines.size();
  int line_label_size = lines[0].second.size();
  for(int i = 0; i < line_size; i++){
    vector<float> v;
    for(int j = 0; j < line_label_size; j+=2){
      int x = lines[i].second[j]*img_width;
      int y = lines[i].second[j+1]*img_height;
      v.push_back(x);
      v.push_back(y);
    }
    gt_coords.push_back(v);
  }

}

void DisplayTool::EnlargeBoundingBox(const vector<cv::Point>& box_coords,
    vector<cv::Point>& larger_box_coords)
{
  int img_width = box_coords[1].x - box_coords[0].x;
  int img_height = box_coords[1].y - box_coords[0].y;
  // int horizontal_offset = img_width*0.0;
  // int vertical_offset = img_height*0.0;
  int horizontal_offset = img_width*0.1;
  int vertical_offset = img_height*0.1;
  // int horizontal_offset = img_width*0.15;
  // int vertical_offset = img_height*0.15;

  larger_box_coords[0].x=box_coords[0].x - horizontal_offset*3/2;
  if(larger_box_coords[0].x<0) larger_box_coords[0].x=0;

  larger_box_coords[0].y=box_coords[0].y - vertical_offset*3/2;
  if(larger_box_coords[0].y<0) larger_box_coords[0].y=0;

  larger_box_coords[1].x=box_coords[1].x + horizontal_offset/2;
  if(larger_box_coords[1].x>640-1) larger_box_coords[1].x=640-1;

  larger_box_coords[1].y=box_coords[1].y + vertical_offset/2;
  if(larger_box_coords[1].y>480-1) larger_box_coords[1].y=480-1;
}

cv::Mat DisplayTool::DisplayBoundingBox(cv::Mat src, string mode, string windowName,
  cv::Point pre_tl, cv::Point pre_br, cv::Point gt_tl, cv::Point gt_br)
{
  cv::Mat dst = src.clone();
  // predict with red
  cv::circle(dst, pre_tl, 3, cv::Scalar(0,0,255), 3); 
  cv::circle(dst, pre_br, 3, cv::Scalar(0,0,255), 3); 
    cv::Rect pre_rect(pre_tl, pre_br);
    cv::rectangle(dst, pre_rect, cv::Scalar(0,0,255));

  if(mode != "TestMode"){
    // ground truth with green
    cv::circle(dst, gt_tl, 3, cv::Scalar(0,255,0), 3); 
    cv::circle(dst, gt_br, 3, cv::Scalar(0,255,0), 3); 
      cv::Rect gt_rect(gt_tl, gt_br);
      cv::rectangle(dst, gt_rect, cv::Scalar(0,255,0));
  }  

  cv::imshow(windowName ,dst);

  cv::waitKey(WAITTIME);
  return dst;
}

cv::Mat DisplayTool::DisplayBoundingBoxWithCenter(cv::Mat src, string mode, string windowName,
  cv::Point pre_tl, cv::Point pre_br, cv::Point gt_tl, cv::Point gt_br)
{
  cv::Mat dst = src.clone();
  // predict with red
  cv::circle(dst, pre_tl, 3, cv::Scalar(0,0,255), 3); 
  cv::circle(dst, pre_br, 3, cv::Scalar(0,0,255), 3); 
    cv::Rect pre_rect(pre_tl, pre_br);
    cv::rectangle(dst, pre_rect, cv::Scalar(0,0,255));

  if(mode != "TestMode"){
    // ground truth with green
    cv::circle(dst, gt_tl, 3, cv::Scalar(0,255,0), 3); 
    cv::circle(dst, gt_br, 3, cv::Scalar(0,255,0), 3); 
      cv::Rect gt_rect(gt_tl, gt_br);
      cv::rectangle(dst, gt_rect, cv::Scalar(0,255,0));
  }  
  cv::Point center((pre_tl.x+pre_br.x)/2, (pre_tl.y+pre_br.y)/2);
  cv::circle(dst, center, 3, cv::Scalar(0,255,0), 3); 

  cv::imshow(windowName ,dst);

  cv::waitKey(WAITTIME);
  return dst;
}

cv::Mat DisplayTool::DisplayFingerPoints(cv::Mat src, string mode,
  cv::Point pre_ft, cv::Point pre_jnt, cv::Point gt_ft, cv::Point gt_jnt)
{
  cv::Mat dst = src.clone();
  // predict with red
  cv::circle(dst, pre_ft, 3, cv::Scalar(0,0,255), 3); 
  cv::circle(dst, pre_jnt, 3, cv::Scalar(0,0,255), 3);  

  if(mode != "TestMode"){
    // ground truth with green
    cv::circle(dst, gt_ft, 3, cv::Scalar(0,255,0), 3); 
    cv::circle(dst, gt_jnt, 3, cv::Scalar(0,255,0), 3); 
  } 

  cv::imshow("Display Fingertip!",dst);

  // cv::waitKey(WAITTIME);
  return dst;
}

cv::Mat DisplayTool::DisplayPoints(cv::Mat src, string mode,
  cv::Point pre_tl, cv::Point pre_br, cv::Point gt_tl, cv::Point gt_br,
  cv::Point pre_ft, cv::Point pre_jnt, cv::Point gt_ft, cv::Point gt_jnt)
{
  cv::Mat dst = src.clone();
  // predict with red
  cv::circle(dst, pre_tl, 3, cv::Scalar(0,0,255), 3); 
  cv::circle(dst, pre_br, 3, cv::Scalar(0,0,255), 3); 
  cv::Rect pre_rect(pre_tl, pre_br);
  cv::rectangle(dst, pre_rect, cv::Scalar(0,0,255));

  // predict with red
  cv::circle(dst, pre_ft, 3, cv::Scalar(0,0,255), 3); 
  cv::circle(dst, pre_jnt, 3, cv::Scalar(0,0,255), 3);

  if(mode != "TestMode"){
    // ground truth with green
    cv::circle(dst, gt_tl, 3, cv::Scalar(0,255,0), 3); 
    cv::circle(dst, gt_br, 3, cv::Scalar(0,255,0), 3); 
      cv::Rect gt_rect(gt_tl, gt_br);
      cv::rectangle(dst, gt_rect, cv::Scalar(0,255,0));

      // ground truth with green
    cv::circle(dst, gt_ft, 3, cv::Scalar(0,255,0), 3); 
    cv::circle(dst, gt_jnt, 3, cv::Scalar(0,255,0), 3); 
  }

  cv::imshow("Display All!",dst);
  return dst;
}


void DisplayTool::CutROI(const cv::Mat& src, cv::Mat& dst, cv::Point pre_tl, cv::Point pre_br)
{
  cv::Mat roi(src, cv::Rect(pre_tl, pre_br));
  roi.copyTo(dst);
}