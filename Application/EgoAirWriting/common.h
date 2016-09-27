#ifndef COMMON
#define COMMON

#include <string>
#include <vector>
#include <time.h>
#include <opencv2/opencv.hpp>

#include "caffe/blob.hpp"   // for net foward
#include "caffe/net.hpp"    // for net forward

#include "iRecognize.h" // for writing recognition

#include <QDir>
#include <QDebug>
#include <QShortcut>

using caffe::Blob;
using caffe::Net;
using caffe::Caffe;
using boost::shared_ptr;
using namespace cv;


#ifndef BREAKPOINT
#define BREAKPOINT  LOG(ERROR)<<"LOG for break point here"
#endif

/**
enum of status
*/

enum GesStatus{
    STATUS_BG=0,
    STATUS_CLOSE,
    STATUS_OPEN,
    STATUS_LSHAPE,
    STATUS_ISHAPE,
    STATUS_VICTORY,
    STATUS_FIST,
};

#define COLOR_RED cv::Scalar(0,0,255)
#define COLOR_GREEN cv::Scalar(0,255,0)
#define COLOR_BLUE cv::Scalar(255,0,0)
#define COLOR_YELLOW cv::Scalar(255,255,0)

#define SRC_SIZE cv::Size(640,480)

#define RECT_LINE 4
#define POINT_RAIUS 2

#endif // COMMON

