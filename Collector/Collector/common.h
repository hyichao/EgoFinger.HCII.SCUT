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

#define COLLECT_PARAM_SingleOne_COUNT (8)
#define COLLECT_PARAM_SingleTwo_COUNT (12)
#define COLLECT_PARAM_SingleThree_COUNT (16)
#define COLLECT_PARAM_SingleFour_COUNT (20)
#define COLLECT_PARAM_SingleFive_COUNT (24)
#define COLLECT_PARAM_SingleSix_COUNT (12)
#define COLLECT_PARAM_SingleSeven_COUNT (16)
#define COLLECT_PARAM_SingleEight_COUNT (12)
#define COLLECT_PARAM_SingleNine_COUNT (8)
#define COLLECT_PARAM_SingleGood_COUNT (8)
#define COLLECT_PARAM_SingleBad_COUNT (8)

#define COLLECT_PARAM_PairSix_COUNT (32)
#define COLLECT_PARAM_PairSeven_COUNT (36)
#define COLLECT_PARAM_PairEight_COUNT (40)
#define COLLECT_PARAM_PairNine_COUNT (44)
#define COLLECT_PARAM_PairTen_COUNT (48)
