#include "coordtool.h"

CoordTool::CoordTool()
{

}

CoordTool::~CoordTool()
{

}

void CoordTool::RotatePoints(cv::Point& in_point, cv::Point& out_point, cv::Mat& rot_mat)
{
    double a11 = rot_mat.at<double>(0,0);
    double a12 = rot_mat.at<double>(0,1);
    double a21 = rot_mat.at<double>(1,0);
    double a22 = rot_mat.at<double>(1,1);
    double b11 = rot_mat.at<double>(0,2);
    double b12 = rot_mat.at<double>(1,2);
    // rotate points
    out_point.x = (in_point.x*a11+in_point.y*a12+b11);
    out_point.y = (in_point.x*a21+in_point.y*a22+b12);
}

void CoordTool::GetMinBoundingRect(vector<cv::Point>& rect, vector<cv::Point>& minBoundRect)
{
    CHECK_EQ(rect.size(), 4);
    minBoundRect.assign(2,cv::Point(0,0));
    minBoundRect[0].x = min<float>(min<float>(rect[0].x, rect[1].x),min<float>(rect[2].x, rect[3].x));
    minBoundRect[0].y = min<float>(min<float>(rect[0].y, rect[1].y),min<float>(rect[2].y, rect[3].y));
    minBoundRect[1].x = max<float>(max<float>(rect[0].x, rect[1].x),max<float>(rect[2].x, rect[3].x));
    minBoundRect[1].y = max<float>(max<float>(rect[0].y, rect[1].y),max<float>(rect[2].y, rect[3].y));
}

void CoordTool::EnlargeBoundingBox(vector<cv::Point>& in_rect, vector<cv::Point>& out_rect,
                                   float scale, int range_width, int range_height)
{
    int img_width = in_rect[1].x - in_rect[0].x;
    int img_height = in_rect[1].y - in_rect[0].y;
    int horizontal_offset = img_width*scale;
    int vertical_offset = img_height*scale;
    out_rect[0].x=max<int>(in_rect[0].x - horizontal_offset/2,0);
    out_rect[0].y=max<int>(in_rect[0].y - vertical_offset/2,0);
    out_rect[1].x=min<int>(in_rect[1].x + horizontal_offset/2,range_width-1);
    out_rect[1].y=min<int>(in_rect[1].y + vertical_offset/2, range_height-1);
}

void CoordTool::PointVec2Rect(vector<cv::Point>& pointVec, cv::Rect& rect, int range_width, int range_height)
{
    // protect
    for(int i = 0; i < 2; i++){
        pointVec[i].x = min<float>(range_width-1, pointVec[i].x);
        pointVec[i].x = max<float>(0, pointVec[i].x);
        pointVec[i].y = min<float>(range_height-1, pointVec[i].y);
        pointVec[i].y = max<float>(0, pointVec[i].y);
    }

    rect = cv::Rect(pointVec[0],pointVec[1]);
}

void CoordTool::offsetRect(cv::Rect& in_rect, cv::Rect& out_rect, cv::Point track_center, cv::Size original_size){
    out_rect.x = track_center.x-original_size.width/2+in_rect.x;
    out_rect.y = track_center.y-original_size.height/2+in_rect.y;
}
void CoordTool::offsetPoint(cv::Point& in_point, cv::Point& out_point, cv::Point track_center, cv::Size original_size){
    out_point.x = track_center.x-original_size.width/2+in_point.x;
    out_point.y = track_center.y-original_size.height/2+in_point.y;
}
void CoordTool::offsetPoints(vector<cv::Point>& in_points, vector<cv::Point>& out_points, cv::Point track_center, cv::Size original_size){
    for (uint i = 0; i < in_points.size(); ++i)
        CoordTool::offsetPoint(in_points[i],out_points[i],track_center,original_size);
}

void CoordTool::protectRectFromEdge(cv::Rect& rect, int range_width, int range_height){
    rect.x = min<float>(range_width-1, rect.x);
    rect.x = max<float>(0, rect.x);
    rect.y = min<float>(range_height-1, rect.y);
    rect.y = max<float>(0, rect.y);

    rect.width = min<float>(range_width-1-rect.x, rect.width);
    rect.width = max<float>(0, rect.width);
    rect.height = min<float>(range_height-1-rect.y, rect.height);
    rect.height = max<float>(0, rect.height);
}
void CoordTool::protectPointFromEdge(cv::Point& point, int range_width, int range_height){
    point.x = min<float>(range_width-1, point.x);
    point.x = max<float>(0, point.x);
    point.y = min<float>(range_height-1, point.y);
    point.y = max<float>(0, point.y);
}
void CoordTool::protectPointsFromEdge(vector<cv::Point>& points, int range_width, int range_height){
    for (uint i = 0; i < points.size(); ++i)
        CoordTool::protectPointFromEdge(points[i],range_width,range_height);
}

