#include "PointingDirection.h"


PointingDirection::PointingDirection()
{
}


PointingDirection::~PointingDirection()
{
}



void PointingDirection::setPath(string txtPath)
{
	path = txtPath;
}


void PointingDirection::displayHistogram()
{
	// proc txt
	analyzeDirection(path);

	// show hist image
	int scale = 4;
	int binHeight = 256;
	int binNum = DEFAULT_MAX_POINTING_ANGLE;
	Utils::drawHistImageByHistMat(hist, scale, binHeight, binNum, "direction");

	//ofstream outfile("genAngle.txt");
	//for (int i = 0; i < DEFAULT_MAX_POINTING_ANGLE; i++){
	//	outfile << hist.at<int>(0, i) << endl;
	//}
	//outfile.close();
}

//**********
// private methods as follows
//**********

void PointingDirection::initHistMat()
{
	Mat mat(1, DEFAULT_MAX_POINTING_ANGLE, CV_32SC1, Scalar(0));
	hist = mat;
}


void PointingDirection::analyzeDirection(string path)
{
	ifstream infile(path.c_str(), ios::in);
	infile.seekg(0, ios::beg);
	if (!infile){
		cerr << "file could not be open." << endl;
		abort();
	}

	initHistMat();

	string filename;						// image file name 
	double label[DEFAULT_COORD_NUM];		// each frame coords

	int counter = 0;
	while (infile >> filename >> label[0] >> label[1] >> label[2] >> label[3]
		>> label[4] >> label[5] >> label[6] >> label[7] >> label[8]
		>> label[9] >> label[10] >> label[11] >> label[12] >> label[13])
	{
		for (int k = 0; k < 7; k++)
		{
			label[2 * k] *= IMAGE_DEFAULT_WIDTH;
			label[2 * k + 1] *= IMAGE_DEFAULT_HEIGHT;
		}

		double dx = label[6] - label[4];
		double dy = label[7] - label[5];

		double angle = atan2(dx, dy);
		angle = (int)((angle / CV_PI) * 360 + 180);

		if (angle < 360 && angle >=0)
			hist.at<int>(0, (int)angle)++;
		else
			qDebug() << "Error angle: " << angle << endl; 
	}
	infile.close();
}