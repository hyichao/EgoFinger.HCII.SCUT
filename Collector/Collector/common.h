#pragma once

//opencv header
#include <opencv2\opencv.hpp>
#include <opencv\cv.hpp>

//std header
#include <iostream>
#include <fstream>
#include "io.h"

//Qt header
#include <QDebug>
#include <QString>
#include <QMessageBox>

//name space 
using namespace std;
using namespace cv;

#define FRAME_WIDTH  (640)
#define FRAME_HEIGHT (480)
#define FRAME_COL FRAME_WIDTH
#define FRAME_ROW FRAME_HEIGHT

#define COLLECT_PARAM_COUNT (14)