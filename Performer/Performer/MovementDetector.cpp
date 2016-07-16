#include "MovementDetector.h"


MovementDetector::MovementDetector()
{
}


MovementDetector::~MovementDetector()
{
}

void MovementDetector::setTxtPath(string path)
{
	txtInPath = path;
}

void MovementDetector::setTxtOutPath(string path)
{
	txtOutPath = path;
}

void MovementDetector::showMovementHistogram(PointType type)
{
	// proc txt
	processTxtContent();

	// show hist image
	Mat hist = movementMat[type];

	int scale = 4;
	int binHeight = 256;
	int binNum = DEFAULT_MAX_MOVE;
	Utils::drawHistImageByHistMat(hist, scale, binHeight, binNum, "movement");
	
}

void MovementDetector::writeMovementIntoTxt(string path)
{
	Mat hist = movementMat[3];
	string uuid = "fingertip";
	Utils::writeHistMatIntoTxt(hist, path, uuid);
}


//**********
// private methods as follows
//**********

void MovementDetector::initMovementMat()
{
	// eacho row for one point coordinates, eacho col for a bin
	// movement discetance is expected below 36
	int pointNum = DEFAULT_POINT_NUM;
	int maxDistance = DEFAULT_MAX_MOVE;

	for (int i = 0; i < pointNum; i++)
	{
		Mat mat(1, maxDistance, CV_32SC1, Scalar(0));
		movementMat[i] = mat;
	}

}

void MovementDetector::recordInfoIntoMat(double movement[14])
{
	// add one while movement of coordinate i is j,
	for (int i = 0; i < DEFAULT_POINT_NUM; i++)
	{
		double dx = movement[2*i];
		double dy = movement[2*i + 1];
		double dis = sqrt(dx*dx + dy*dy);
		dis = dis>DEFAULT_MAX_MOVE-1 ? -1 : dis;
		
		if (dis < 0) continue;

		if (dis < DEFAULT_MAX_MOVE)
			movementMat[i].at<int>(0, dis)++;
	}
}

void MovementDetector::processTxtContent()
{
	ifstream infile(txtInPath.c_str(), ios::in);
	infile.seekg(0, ios::beg);
	if (!infile){
		cerr << "file could not be open." << endl;
		abort();
	}

	initMovementMat();

	string filename;						// image file name 
	double previous[DEFAULT_COORD_NUM];		// previous frame coords
	double next[DEFAULT_COORD_NUM];			// next frame coords
	double move[DEFAULT_COORD_NUM];			// movement distance
	int counter = 0;
	while (infile >> filename >> next[0] >> next[1] >> next[2] >> next[3]
		>> next[4] >> next[5] >> next[6] >> next[7] >> next[8]
		>> next[9] >> next[10] >> next[11] >> next[12] >> next[13])
	{

		for (int k = 0; k < 7; k++)
		{
			next[2 * k] *= IMAGE_DEFAULT_WIDTH;
			next[2 * k + 1] *= IMAGE_DEFAULT_HEIGHT;
		}

		// calculate movement for each row of txt content
		if (counter != 0)
		{
			for (int i = 0; i < DEFAULT_COORD_NUM; i++)
			{
				move[i] = next[i] - previous[i];	
			}
		}
		// replace old info with new
		for (int j = 0; j < DEFAULT_COORD_NUM; j++)
		{
			previous[j] = next[j];
		}
		counter++;

		// write info into mat
		recordInfoIntoMat(move);
	}

	infile.close();
}
