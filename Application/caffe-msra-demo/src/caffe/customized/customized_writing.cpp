#include "caffe/customized/customized_writing.hpp"  


void WritingTool::init(){
  // writer.open("/home/charlie/VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));
  // if(!writer.isOpened())
  //   LOG(ERROR)<<"Cannot open video writer!";
  // else
  //   LOG(ERROR)<<"Video Writer opened!"; 

  loadClassifier(); 
}

void WritingTool::expire(){
  releaseClassifier();
}

void WritingTool::addPoint(cv::Point sPoint){
  points_.push_back(sPoint);
  smoothPoints();
}


vector<cv::Point> WritingTool::getPoints(){
  return points_;
}

int WritingTool::getPointCount(){
  return points_.size();
}
void WritingTool::clearPoints(){
  points_.erase(points_.begin(), points_.end());
}

void WritingTool::smoothPoints(){
  //TODO
  int size = points_.size();
  if(size<3) 
    return;
  float alpha = 0.5;
  float mid_x = (points_[size-1].x+points_[size-3].x)/2;
  float mid_y = (points_[size-1].y+points_[size-3].y)/2;
  points_[size-2].x=alpha*mid_x+(1-alpha)*points_[size-2].x;
  points_[size-2].y=alpha*mid_y+(1-alpha)*points_[size-2].y;
}

cv::Mat WritingTool::showPointsOnMat(const cv::Mat& src, bool show){
 
  cv::Mat dst;
  src.copyTo(dst);

  int size = points_.size();

  for(int i=0; i<size;i++){
    cv::circle(dst, points_[i], 2, cv::Scalar(0,0,255), 2);
  }
  for(int i=1; i<size;i++){
    cv::line(dst, points_[i-1], points_[i], cv::Scalar(0,0,255), 4);
  }
  if(size>0) 
    cv::circle(dst, points_[size-1], 4, cv::Scalar(0,255,0), 4);

  if(show){
    cv::imshow("Air Writing", dst);    
    // writer<<dst;
    // cv::waitKey(30);
    // cv::waitKey(1);
  }

  return dst;
}

string WritingTool::recognizeCharacter(){

  vector<cv::Point> tem_points(points_);
  int pt_num = tem_points.size();
  int pt[pt_num*2+4];
  for(int i=0;i<pt_num;i++){
    pt[2*i]=tem_points[i].x;
    pt[2*i+1]=tem_points[i].y;  
  }  
  pt[pt_num*2]=-1;
  pt[pt_num*2+1]=0;  
  pt[pt_num*2+2]=-1;
  pt[pt_num*2+3]=-1;

  const int candidate_count = 10;
  float fScan[candidate_count*2];
  char candidate[candidate_count*2];
  recognize(candidate, pt, pt_num, 0x00000400, 0, fScan);

  string cdd="";
  for(int i=0; i< candidate_count; i++){
    char* unicode = new char[2];
    unicode[0] = candidate[i];
    unicode[1] = candidate[i+1];
    char* utf8 = new char[2];
    memset(utf8, 0, sizeof(char)*2);
    WritingTool::UnicodeToUTF8(utf8, unicode);
    string str(utf8,3);
    cdd+=str;
  }

  LOG(ERROR)<<"No.1 candidate: "<<cdd.substr(0,3)
            <<"No.2 candidate: "<<cdd.substr(3,3)
            <<"No.3 candidate: "<<cdd.substr(6,3)
            <<"No.4 candidate: "<<cdd.substr(9,3)
            <<"No.5 candidate: "<<cdd.substr(12,3)
            <<"No.6 candidate: "<<cdd.substr(15,3)
            <<"No.7 candidate: "<<cdd.substr(18,3)
            <<"No.8 candidate: "<<cdd.substr(21,3)
            <<"No.9 candidate: "<<cdd.substr(24,3)
            <<"No.10 candidate: "<<cdd.substr(27,3)
                        ;

  // char* unicode = new char[2]; //啊 0xb0a1;
  // unicode[0] = candidate[0];
  // unicode[1] = candidate[1];
  // char* utf8 = new char[2];
  // memset(utf8, 0, sizeof(char)*2);
  // WritingTool::UnicodeToUTF8(utf8, unicode);
  // string str(utf8,3);
  // LOG(ERROR)<<"No.1 candidate: "<<str;

  return cdd;
}