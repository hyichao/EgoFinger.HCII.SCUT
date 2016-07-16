#include <opencv2/opencv.hpp>


#include <iostream>
#include <fstream>
#include <cmath>
#include <direct.h>

#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QFileDialog>

using namespace std;
using namespace cv;

#define IMAGE_DEFAULT_WIDTH (640)
#define IMAGE_DEFAULT_HEIGHT (480)
#define DEFAULT_FPS (30)
#define DEFAULT_COORD_NUM (14)
#define DEFAULT_POINT_NUM (DEFAULT_COORD_NUM/2)
#define DEFAULT_MAX_MOVE (72)
#define DEFAULT_MAX_FINGER_LENGTH (120)
#define DEFAULT_MAX_POINTING_ANGLE (360)
