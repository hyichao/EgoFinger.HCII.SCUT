#ifndef COORDTOOL_H
#define COORDTOOL_H

#include "common.h"

class CoordTool
{
public:
    CoordTool();
    ~CoordTool();

    static void RotatePoints(cv::Point& in_point, cv::Point& out_point, cv::Mat& rot_mat);
    static void GetMinBoundingRect(vector<cv::Point>& rect, vector<cv::Point>& minBoundRect);
    static void EnlargeBoundingBox(vector<cv::Point>& in_rect, vector<cv::Point>& out_rect,
                                   float scale, int range_width, int range_height);

    static void PointVec2Rect(vector<cv::Point>& pointVec, cv::Rect& rect, int range_width, int range_height);

    //for addaptive camera
    static void offsetRect(cv::Rect& in_rect, cv::Rect& out_rect, cv::Point track_center, cv::Size original_size);
    static void offsetPoint(cv::Point& in_point, cv::Point& out_point, cv::Point track_center, cv::Size original_size);
    static void offsetPoints(vector<cv::Point>& in_points, vector<cv::Point>& out_points, cv::Point track_center, cv::Size original_size);

    static void protectRectFromEdge(cv::Rect& rect, int range_width, int range_height);
    static void protectPointFromEdge(cv::Point& point, int range_width, int range_height);
    static void protectPointsFromEdge(vector<cv::Point>& points, int range_width, int range_height);

};

#endif // COORDTOOL_H
