#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "common.h"

class Processor
{
private:
    Mat src;
    Mat dst;

public:

	//totally 7 points for collection
	float tlx, tly;//BoundingBoxTopLeft
	float brx, bry;//BoundingBoxBottmRight
	float iftx, ifty;//IndexFingertip
	float ifjx, ifjy;//IndexFingerJoint
	float tfjx, tfjy;//TailFingerJoint
	float btx, bty;//ThumbTip
	float bjx, bjy;//ThumbJoint

	int clickedTimes;
    bool hasFinished;

public:
    Processor();
    ~Processor();


	void splitVideo(QString videoPath, QString dir, QString baseName);


    //mat method
    void readImage(string path);
    void addCircleInImage(int x, int y);
    bool checkPoints();

	//display
    Mat showDstImage();
	Mat showRecordedImage(vector<float> v);
};

#endif // PROCESSOR_H
