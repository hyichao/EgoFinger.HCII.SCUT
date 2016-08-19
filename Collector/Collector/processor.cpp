#include "processor.h"


Processor::Processor()
{

}

Processor::~Processor()
{

}

//*****************
// 读入图片
//*****************
void Processor::readImage(string path)
{
	src = imread(path);

	if (src.empty())
	{
		qDebug("error while reading image");
		return;
	}

	src.copyTo(dst);
	cv::resize(dst, dst, cv::Size(640, 480));

	clickedTimes = 0;
	hasFinished = false;

	//###
	//###totally 24 points for collection
	//###right hand
	tlx = -1; tly = -1;//BoundingBoxTopLeft
	brx = -1; bry = -1;//BoundingBoxBottmRight
	iftx = -1; ifty = -1;//IndexFingerTip
	ifjx = -1; ifjy = -1;//IndexFingerJoint
	mftx = -1; mfty = -1;//MiddleFingerTip
	mfjx = -1; mfjy = -1;//MiddleFingerJoint
	rftx = -1; rfty = -1;//RingFingerTip
	rfjx = -1; rfjy = -1;//RingFingerJoint
	tftx = -1; tfty = -1;//TailFingerTip
	tfjx = -1; tfjy = -1;//TailFingerJoint
	btx = -1; bty = -1;//ThumbTip
	bjx = -1; bjy = -1;//ThumbJoint
	//###left hand
	tlx_l = -1; tly_l = -1;//BoundingBoxTopLeft
	brx_l = -1; bry_l = -1;//BoundingBoxBottmRight
	iftx_l = -1; ifty_l = -1;//IndexFingerTip
	ifjx_l = -1; ifjy_l = -1;//IndexFingerJoint
	mftx_l = -1; mfty_l = -1;//MiddleFingerTip
	mfjx_l = -1; mfjy_l = -1;//MiddleFingerJoint
	rftx_l = -1; rfty_l = -1;//RingFingerTip
	rfjx_l = -1; rfjy_l = -1;//RingFingerJoint
	tftx_l = -1; tfty_l = -1;//TailFingerTip
	tfjx_l = -1; tfjy_l = -1;//TailFingerJoint
	btx_l = -1; bty_l = -1;//ThumbTip
	bjx_l = -1; bjy_l = -1;//ThumbJoint
}

//*****************
// 每次鼠标点击就输入该点
//*****************
//###
void Processor::addCircleInImage(int x, int y, QString videoType, ImageWidget* imgWidget)
{
	clickedTimes++;
	cv::Rect rect;
	if (videoType == "SingleOne")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleTwo")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleThree")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleFour")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 9:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 10:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleFive")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 9:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 10:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 11:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 12:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleSix")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 4:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 5:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 6:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleSeven")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 6:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 7:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 8:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleEight")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 6:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleNine")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleGood")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 4:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "SingleBad")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 4:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "PairSix")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 9:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 10:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 11:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 12:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);

			imgWidget->isOn = true;	//###

			break;

		case 13:
			tlx_l = x; tly_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 14:
			brx_l = x; bry_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx_l, tly_l, brx_l - tlx_l, bry_l - tly_l);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 15:
			iftx_l = x; ifty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 16:
			ifjx_l = x; ifjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "PairSeven")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 9:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 10:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 11:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 12:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);

			imgWidget->isOn = true;	//###

			break;

		case 13:
			tlx_l = x; tly_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 14:
			brx_l = x; bry_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx_l, tly_l, brx_l - tlx_l, bry_l - tly_l);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 15:
			iftx_l = x; ifty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 16:
			ifjx_l = x; ifjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 17:
			mftx_l = x; mfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 18:
			mfjx_l = x; mfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "PairEight")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 9:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 10:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 11:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 12:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);

			imgWidget->isOn = true;	//###

			break;

		case 13:
			tlx_l = x; tly_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 14:
			brx_l = x; bry_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx_l, tly_l, brx_l - tlx_l, bry_l - tly_l);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 15:
			iftx_l = x; ifty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 16:
			ifjx_l = x; ifjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 17:
			mftx_l = x; mfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 18:
			mfjx_l = x; mfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 19:
			btx_l = x; bty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 20:
			bjx_l = x; bjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "PairNine")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 9:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 10:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 11:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 12:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);

			imgWidget->isOn = true;	//###

			break;

		case 13:
			tlx_l = x; tly_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 14:
			brx_l = x; bry_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx_l, tly_l, brx_l - tlx_l, bry_l - tly_l);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 15:
			iftx_l = x; ifty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 16:
			ifjx_l = x; ifjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 17:
			mftx_l = x; mfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 18:
			mfjx_l = x; mfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 19:
			rftx_l = x; rfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 20:
			rfjx_l = x; rfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 21:
			tftx_l = x; tfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 22:
			tfjx_l = x; tfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			hasFinished = true;
			break;
		}
	}
	else if (videoType == "PairTen")
	{
		switch (clickedTimes)
		{
		case 1:
			tlx = x; tly = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 2:
			brx = x; bry = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx, tly, brx - tlx, bry - tly);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 3:
			iftx = x; ifty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 4:
			ifjx = x; ifjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 5:
			mftx = x; mfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 6:
			mfjx = x; mfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 7:
			rftx = x; rfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 8:
			rfjx = x; rfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 9:
			tftx = x; tfty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 10:
			tfjx = x; tfjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 11:
			btx = x; bty = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 12:
			bjx = x; bjy = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);

			imgWidget->isOn = true;	//###

			break;

		case 13:
			tlx_l = x; tly_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			break;
		case 14:
			brx_l = x; bry_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 3);
			rect = cv::Rect_<int>(tlx_l, tly_l, brx_l - tlx_l, bry_l - tly_l);
			rectangle(dst, rect, cv::Scalar(0, 0, 0), 1);

			imgWidget->isOn = false;	//###

			break;
		case 15:
			iftx_l = x; ifty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 16:
			ifjx_l = x; ifjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 255), 3);
			break;
		case 17:
			mftx_l = x; mfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 18:
			mfjx_l = x; mfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 255, 0), 3);
			break;
		case 19:
			rftx_l = x; rfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 20:
			rfjx_l = x; rfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 255), 3);
			break;
		case 21:
			tftx_l = x; tfty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 22:
			tfjx_l = x; tfjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(255, 0, 0), 3);
			break;
		case 23:
			btx_l = x; bty_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			break;
		case 24:
			bjx_l = x; bjy_l = y;
			circle(dst, cv::Point(x, y), 3, cv::Scalar(0, 255, 0), 3);
			hasFinished = true;
			break;

		}
	}
	else
	{
		return;
	}
}

//*****************
// 检查数据点是否越界
//*****************
//###
bool Processor::checkPoints(QString videoType)
{
	if (!hasFinished)
		return false;
	//check tl and br
	if (brx<tlx || bry<tly)
	{
		return false;
	}
	//keep ift inside
	if (iftx != -1)	//###判断手势中是否含有食指指尖
	{
		if (iftx>brx || ifty>bry || iftx < tlx || ifty < tly)
		{
			return false;
		}
	}
	//keep ifj inside
	if (ifjx != -1)	//###判断手势中是否含有食指关节
	{
		if (ifjx>brx || ifjy>bry || ifjx < tlx || ifjy < tly)
		{
			return false;
		}
	}
	//keep mft inside
	if (mftx != -1)
	{
		if (mftx>brx || mfty>bry || mftx < tlx || mfty < tly)
		{
			return false;
		}
	}
	//keep mfj inside
	if (mfjx != -1)
	{
		if (mfjx>brx || mfjy>bry || mfjx < tlx || mfjy < tly)
		{
			return false;
		}
	}
	//keep rft inside
	if (rftx != -1)
	{
		if (rftx>brx || rfty>bry || rftx < tlx || rfty < tly)
		{
			return false;
		}
	}
	//keep rfj inside
	if (rfjx != -1)
	{
		if (rfjx>brx || rfjy>bry || rfjx < tlx || rfjy < tly)
		{
			return false;
		}
	}
	//keep tft inside
	if (tftx != -1)
	{
		if (tftx>brx || tfty>bry || tftx < tlx || tfty < tly)
		{
			return false;
		}
	}
	//keep tfj inside
	if (tfjx != -1)
	{
		if (tfjx>brx || tfjy>bry || tfjx < tlx || tfjy < tly)
		{
			return false;
		}
	}
	//keep bt inside
	if (btx != -1)
	{
		if (btx>brx || bty>bry || btx < tlx || bty < tly)
		{
			return false;
		}
	}
	//keep bj inside
	if (bjx != -1)
	{
		if (bjx>brx || bjy>bry || bjx < tlx || bjy < tly)
		{
			return false;
		}
	}

	if (tlx_l != -1)	//###判断是否为双手的手势
	{
		//check tl_l and br_l
		if (brx_l<tlx_l || bry_l<tly_l)
		{
			return false;
		}
		//keep ift inside
		if (iftx_l != -1)	//###判断手势中是否含有食指指尖
		{
			if (iftx_l>brx_l || ifty_l>bry_l || iftx_l < tlx_l || ifty_l < tly_l)
			{
				return false;
			}
		}
		//keep ifj inside
		if (ifjx_l != -1)	//###判断手势中是否含有食指关节
		{
			if (ifjx_l>brx_l || ifjy_l>bry_l || ifjx_l < tlx_l || ifjy_l < tly_l)
			{
				return false;
			}
		}
		//keep mft inside
		if (mftx_l != -1)
		{
			if (mftx_l>brx_l || mfty_l>bry_l || mftx_l < tlx_l || mfty_l < tly_l)
			{
				return false;
			}
		}
		//keep mfj inside
		if (mfjx_l != -1)
		{
			if (mfjx_l>brx_l || mfjy_l>bry_l || mfjx_l < tlx_l || mfjy_l < tly_l)
			{
				return false;
			}
		}
		//keep rft inside
		if (rftx_l != -1)
		{
			if (rftx_l>brx_l || rfty_l>bry_l || rftx_l < tlx_l || rfty_l < tly_l)
			{
				return false;
			}
		}
		//keep rfj inside
		if (rfjx_l != -1)
		{
			if (rfjx_l>brx_l || rfjy_l>bry_l || rfjx_l < tlx_l || rfjy_l < tly_l)
			{
				return false;
			}
		}
		//keep tft inside
		if (tftx_l != -1)
		{
			if (tftx_l>brx_l || tfty_l>bry_l || tftx_l < tlx_l || tfty_l < tly_l)
			{
				return false;
			}
		}
		//keep tfj inside
		if (tfjx_l != -1)
		{
			if (tfjx_l>brx_l || tfjy_l>bry_l || tfjx_l < tlx_l || tfjy_l < tly_l)
			{
				return false;
			}
		}
		//keep bt inside
		if (btx_l != -1)
		{
			if (btx_l>brx_l || bty_l>bry_l || btx_l < tlx_l || bty_l < tly_l)
			{
				return false;
			}
		}
		//keep bj inside
		if (bjx_l != -1)
		{
			if (bjx_l>brx_l || bjy_l>bry_l || bjx_l < tlx_l || bjy_l < tly_l)
			{
				return false;
			}
		}
	}

	return true;

}

//*****************
// 输出当前图像（加点中）
//*****************
Mat Processor::showDstImage()
{
	return dst;
}

//*****************
// 输入图像（对于已有数据）
//*****************
Mat Processor::showRecordedImage(vector<float> v, QString videoType)
{

	if (videoType == "SingleOne")
	{
		return prepareRecordedImageSingleOne(v);
	}
	if (videoType == "SingleTwo")
	{
		return prepareRecordedImageSingleTwo(v);
	}
	if (videoType == "SingleThree")
	{
		return prepareRecordedImageSingleThree(v);
	}
	if (videoType == "SingleFour")
	{
		return prepareRecordedImageSingleFour(v);
	}
	if (videoType == "SingleFive")
	{
		return prepareRecordedImageSingleFive(v);
	}
	if (videoType == "SingleSix")
	{
		return prepareRecordedImageSingleSix(v);
	}
	if (videoType == "SingleSeven")
	{
		return prepareRecordedImageSingleSeven(v);
	}
	if (videoType == "SingleEight")
	{
		return prepareRecordedImageSingleEight(v);
	}
	if (videoType == "SingleNine")
	{
		return prepareRecordedImageSingleNine(v);
	}
	if (videoType == "SingleGood")
	{
		return prepareRecordedImageSingleGood(v);
	}
	if (videoType == "SingleBad")
	{
		return prepareRecordedImageSingleBad(v);
	}
	if (videoType == "PairSix")
	{
		return prepareRecordedImagePairSix(v);
	}
	if (videoType == "PairSeven")
	{
		return prepareRecordedImagePairSeven(v);
	}
	if (videoType == "PairEight")
	{
		return prepareRecordedImagePairEight(v);
	}
	if (videoType == "PairNine")
	{
		return prepareRecordedImagePairNine(v);
	}
	if (videoType == "PairTen")
	{
		return prepareRecordedImagePairTen(v);
	}
	QMessageBox::information(NULL, QObject::tr("videoType"), QObject::tr("videoType Error!"));
	abort();

}

#include "recorder.h"
//*****************
// 视频流分割为帧图
//*****************
void Processor::splitVideo(QString videoPath, QString dir, QString baseName)
{
	VideoCapture cap;
	cv::String str = videoPath.toStdString().data();

	Recorder::writeLog(videoPath);

	cap.open(str);
	if (!cap.isOpened()){
		QMessageBox::information(NULL, "Path", "Didn't Select a Correct Video File.");
		return;
	}


	int totalFrameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);
	for (int i = 0; i < totalFrameNumber; i++)
	{
		Mat frame;
		cap.read(frame);	//###修改，原来是cap>>frame，但是运行不了
		cv::resize(frame, frame, cv::Size(640, 480));

		QString writeImgPath = dir + "/" + baseName + "_color_" + QString::number(i) + ".png";
		imwrite(writeImgPath.toStdString().data(), frame);
		imshow("show", frame);
		waitKey(10);
	}
	destroyAllWindows();
}

//###

QString Processor::getVideoType(QString baseName)
{
	if (baseName.length() == 0)
	{
		QMessageBox::information(NULL, QObject::tr("Path"), QObject::tr("Didn't Select a Correct Video File."));
		return 0;
	}
	QString handNum;
	QString handGesture;
	handNum = baseName.section('_', 1, 1);
	handGesture = baseName.section('_', 2, 2);
	return handNum + handGesture;
}

Mat Processor::prepareRecordedImageSingleOne(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleTwo(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleThree(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleFour(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];
	tftx = v[16]; tfty = v[17];
	tfjx = v[18]; tfjy = v[19];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleFive(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];
	tftx = v[16]; tfty = v[17];
	tfjx = v[18]; tfjy = v[19];
	btx = v[20]; bty = v[21];
	bjx = v[22]; bjy = v[23];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleSix(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	tftx = v[4]; tfty = v[5];
	tfjx = v[6]; tfjy = v[7];
	btx = v[8]; bty = v[9];
	bjx = v[10]; bjy = v[11];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleSeven(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	tftx = v[8]; tfty = v[9];
	tfjx = v[10]; tfjy = v[11];
	btx = v[12]; bty = v[13];
	bjx = v[14]; bjy = v[15];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleEight(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	btx = v[8]; bty = v[9];
	bjx = v[10]; bjy = v[11];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleNine(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleGood(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	btx = v[4]; bty = v[5];
	bjx = v[6]; bjy = v[7];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImageSingleBad(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	btx = v[4]; bty = v[5];
	bjx = v[6]; bjy = v[7];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImagePairSix(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];
	tftx = v[16]; tfty = v[17];
	tfjx = v[18]; tfjy = v[19];
	btx = v[20]; bty = v[21];
	bjx = v[22]; bjy = v[23];

	tlx_l = v[24]; tly_l = v[25];
	brx_l = v[26]; bry_l = v[27];
	iftx_l = v[28]; ifty_l = v[29];
	ifjx_l = v[30]; ifjy_l = v[31];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);

	cv::circle(recordedDst, cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx_l*FRAME_WIDTH, ifty_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx_l*FRAME_WIDTH, ifjy_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::Rect rect_l(cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));
	cv::rectangle(recordedDst, rect_l, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImagePairSeven(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];
	tftx = v[16]; tfty = v[17];
	tfjx = v[18]; tfjy = v[19];
	btx = v[20]; bty = v[21];
	bjx = v[22]; bjy = v[23];

	tlx_l = v[24]; tly_l = v[25];
	brx_l = v[26]; bry_l = v[27];
	iftx_l = v[28]; ifty_l = v[29];
	ifjx_l = v[30]; ifjy_l = v[31];
	mftx_l = v[32]; mfty_l = v[33];
	mfjx_l = v[34]; mfjy_l = v[35];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);

	cv::circle(recordedDst, cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx_l*FRAME_WIDTH, ifty_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx_l*FRAME_WIDTH, ifjy_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx_l*FRAME_WIDTH, mfty_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx_l*FRAME_WIDTH, mfjy_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::Rect rect_l(cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));
	cv::rectangle(recordedDst, rect_l, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImagePairEight(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];
	tftx = v[16]; tfty = v[17];
	tfjx = v[18]; tfjy = v[19];
	btx = v[20]; bty = v[21];
	bjx = v[22]; bjy = v[23];

	tlx_l = v[24]; tly_l = v[25];
	brx_l = v[26]; bry_l = v[27];
	iftx_l = v[28]; ifty_l = v[29];
	ifjx_l = v[30]; ifjy_l = v[31];
	mftx_l = v[32]; mfty_l = v[33];
	mfjx_l = v[34]; mfjy_l = v[35];
	btx_l = v[36]; bty_l = v[37];
	bjx_l = v[38]; bjy_l = v[39];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);

	cv::circle(recordedDst, cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx_l*FRAME_WIDTH, ifty_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx_l*FRAME_WIDTH, ifjy_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx_l*FRAME_WIDTH, mfty_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx_l*FRAME_WIDTH, mfjy_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(btx_l*FRAME_WIDTH, bty_l*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx_l*FRAME_WIDTH, bjy_l*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::Rect rect_l(cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));
	cv::rectangle(recordedDst, rect_l, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImagePairNine(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];
	tftx = v[16]; tfty = v[17];
	tfjx = v[18]; tfjy = v[19];
	btx = v[20]; bty = v[21];
	bjx = v[22]; bjy = v[23];

	tlx_l = v[24]; tly_l = v[25];
	brx_l = v[26]; bry_l = v[27];
	iftx_l = v[28]; ifty_l = v[29];
	ifjx_l = v[30]; ifjy_l = v[31];
	mftx_l = v[32]; mfty_l = v[33];
	mfjx_l = v[34]; mfjy_l = v[35];
	rftx_l = v[36]; rfty_l = v[37];
	rfjx_l = v[38]; rfjy_l = v[39];
	tftx_l = v[40]; tfty_l = v[41];
	tfjx_l = v[42]; tfjy_l = v[43];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);

	cv::circle(recordedDst, cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx_l*FRAME_WIDTH, ifty_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx_l*FRAME_WIDTH, ifjy_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx_l*FRAME_WIDTH, mfty_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx_l*FRAME_WIDTH, mfjy_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx_l*FRAME_WIDTH, rfty_l*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx_l*FRAME_WIDTH, rfjy_l*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx_l*FRAME_WIDTH, tfty_l*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx_l*FRAME_WIDTH, tfjy_l*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::Rect rect_l(cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));
	cv::rectangle(recordedDst, rect_l, Scalar(0, 0, 0));

	return recordedDst;
}

Mat Processor::prepareRecordedImagePairTen(vector<float> v)
{
	Mat recordedDst;

	tlx = v[0]; tly = v[1];
	brx = v[2]; bry = v[3];
	iftx = v[4]; ifty = v[5];
	ifjx = v[6]; ifjy = v[7];
	mftx = v[8]; mfty = v[9];
	mfjx = v[10]; mfjy = v[11];
	rftx = v[12]; rfty = v[13];
	rfjx = v[14]; rfjy = v[15];
	tftx = v[16]; tfty = v[17];
	tfjx = v[18]; tfjy = v[19];
	btx = v[20]; bty = v[21];
	bjx = v[22]; bjy = v[23];

	tlx_l = v[24]; tly_l = v[25];
	brx_l = v[26]; bry_l = v[27];
	iftx_l = v[28]; ifty_l = v[29];
	ifjx_l = v[30]; ifjy_l = v[31];
	mftx_l = v[32]; mfty_l = v[33];
	mfjx_l = v[34]; mfjy_l = v[35];
	rftx_l = v[36]; rfty_l = v[37];
	rfjx_l = v[38]; rfjy_l = v[39];
	tftx_l = v[40]; tfty_l = v[41];
	tfjx_l = v[42]; tfjy_l = v[43];
	btx_l = v[44]; bty_l = v[45];
	bjx_l = v[46]; bjy_l = v[47];

	src.copyTo(recordedDst);
	cv::circle(recordedDst, cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx*FRAME_WIDTH, ifty*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx*FRAME_WIDTH, ifjy*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx*FRAME_WIDTH, mfty*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx*FRAME_WIDTH, mfjy*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx*FRAME_WIDTH, rfty*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx*FRAME_WIDTH, rfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx*FRAME_WIDTH, tfty*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx*FRAME_WIDTH, tfjy*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx*FRAME_WIDTH, bty*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx*FRAME_WIDTH, bjy*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);

	cv::circle(recordedDst, cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT), 3, Scalar(0, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(iftx_l*FRAME_WIDTH, ifty_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(ifjx_l*FRAME_WIDTH, ifjy_l*FRAME_HEIGHT), 3, Scalar(0, 255, 255), 3);
	cv::circle(recordedDst, cv::Point(mftx_l*FRAME_WIDTH, mfty_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(mfjx_l*FRAME_WIDTH, mfjy_l*FRAME_HEIGHT), 3, Scalar(255, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(rftx_l*FRAME_WIDTH, rfty_l*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(rfjx_l*FRAME_WIDTH, rfjy_l*FRAME_HEIGHT), 3, Scalar(255, 0, 255), 3);
	cv::circle(recordedDst, cv::Point(tftx_l*FRAME_WIDTH, tfty_l*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(tfjx_l*FRAME_WIDTH, tfjy_l*FRAME_HEIGHT), 3, Scalar(255, 0, 0), 3);
	cv::circle(recordedDst, cv::Point(btx_l*FRAME_WIDTH, bty_l*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::circle(recordedDst, cv::Point(bjx_l*FRAME_WIDTH, bjy_l*FRAME_HEIGHT), 3, Scalar(0, 255, 0), 3);
	cv::Rect rect(cv::Point(tlx*FRAME_WIDTH, tly*FRAME_HEIGHT), cv::Point(brx*FRAME_WIDTH, bry*FRAME_HEIGHT));
	cv::Rect rect_l(cv::Point(tlx_l*FRAME_WIDTH, tly_l*FRAME_HEIGHT), cv::Point(brx_l*FRAME_WIDTH, bry_l*FRAME_HEIGHT));
	cv::rectangle(recordedDst, rect, Scalar(0, 0, 0));
	cv::rectangle(recordedDst, rect_l, Scalar(0, 0, 0));

	return recordedDst;
}