#include "writing.h"

Writing::Writing()
{
    loadClassifier();
}

Writing::~Writing()
{
    releaseClassifier();
}

void Writing::addPoint(cv::Point sPoint){
  points_.push_back(sPoint);
  smoothPoints();
}

vector<cv::Point> Writing::getPoints(){
  return points_;
}

int Writing::getPointCount(){
  return points_.size();
}
void Writing::clearPoints(){
  points_.erase(points_.begin(), points_.end());
}

void Writing::smoothPoints(){
  int size = points_.size();
  if(size<3)
    return;
  float alpha = 0.5;
  float mid_x = (points_[size-1].x+points_[size-3].x)/2;
  float mid_y = (points_[size-1].y+points_[size-3].y)/2;
  points_[size-2].x=alpha*mid_x+(1-alpha)*points_[size-2].x;
  points_[size-2].y=alpha*mid_y+(1-alpha)*points_[size-2].y;
}

string Writing::recognizeCharacter(){

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

    int GPEN_NUMBER = 0x00000010;
    int GPEN_UPPER = 0x00000001;
    int GPEN_LOWER = 0x00000004;
    int GPEN_CHINESE = 0x00000400;

    recognize(candidate, pt, pt_num, GPEN_NUMBER | GPEN_UPPER | GPEN_LOWER | GPEN_CHINESE, 0, fScan);

    string cdd;
    for(int i=0; i< candidate_count; i++){
      char unicode[2];
      unicode[0] = candidate[i];
      unicode[1] = candidate[i+1];
      char utf8[3];
      memset(utf8, 0, sizeof(char)*3);
      Writing::UnicodeToUTF8(utf8, unicode);
      string str(utf8,3);
      cdd+=str;
    }

  return cdd;
}
