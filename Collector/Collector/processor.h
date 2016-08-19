#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "common.h"
#include "imagewidget.h"	//###

class Processor
{
private:
	Mat src;
	Mat dst;

public:

	//###totally 24 points for collection
	//###right hand
	float tlx, tly;//BoundingBoxTopLeft
	float brx, bry;//BoundingBoxBottmRight
	float iftx, ifty;//IndexFingerTip
	float ifjx, ifjy;//IndexFingerJoint
	float mftx, mfty;//MiddleFingerTip
	float mfjx, mfjy;//MiddleFingerJoint
	float rftx, rfty;//RingFingerTip
	float rfjx, rfjy;//RingFingerJoint
	float tftx, tfty;//TailFingerTip
	float tfjx, tfjy;//TailFingerJoint
	float btx, bty;//ThumbTip
	float bjx, bjy;//ThumbJoint
	//###left hand
	float tlx_l, tly_l;//BoundingBoxTopLeft
	float brx_l, bry_l;//BoundingBoxBottmRight
	float iftx_l, ifty_l;//IndexFingerTip
	float ifjx_l, ifjy_l;//IndexFingerJoint
	float mftx_l, mfty_l;//MiddleFingerTip
	float mfjx_l, mfjy_l;//MiddleFingerJoint
	float rftx_l, rfty_l;//RingFingerTip
	float rfjx_l, rfjy_l;//RingFingerJoint
	float tftx_l, tfty_l;//TailFingerTip
	float tfjx_l, tfjy_l;//TailFingerJoint
	float btx_l, bty_l;//ThumbTip
	float bjx_l, bjy_l;//ThumbJoint

	int clickedTimes;
	bool hasFinished;

public:
	Processor();
	~Processor();


	void splitVideo(QString videoPath, QString dir, QString baseName);

	QString getVideoType(QString baseName);	//###

	//mat method
	void readImage(string path);
	void addCircleInImage(int x, int y, QString videoType, ImageWidget* imgWidget);
	bool checkPoints(QString videoType);

	//display
	Mat showDstImage();
	Mat showRecordedImage(vector<float> v, QString videoType);

	Mat prepareRecordedImageSingleOne(vector<float> v);
	Mat prepareRecordedImageSingleTwo(vector<float> v);
	Mat prepareRecordedImageSingleThree(vector<float> v);
	Mat prepareRecordedImageSingleFour(vector<float> v);
	Mat prepareRecordedImageSingleFive(vector<float> v);
	Mat prepareRecordedImageSingleSix(vector<float> v);
	Mat prepareRecordedImageSingleSeven(vector<float> v);
	Mat prepareRecordedImageSingleEight(vector<float> v);
	Mat prepareRecordedImageSingleNine(vector<float> v);
	Mat prepareRecordedImageSingleGood(vector<float> v);
	Mat prepareRecordedImageSingleBad(vector<float> v);

	Mat prepareRecordedImagePairSix(vector<float> v);
	Mat prepareRecordedImagePairSeven(vector<float> v);
	Mat prepareRecordedImagePairEight(vector<float> v);
	Mat prepareRecordedImagePairNine(vector<float> v);
	Mat prepareRecordedImagePairTen(vector<float> v);

};

#endif // PROCESSOR_H
