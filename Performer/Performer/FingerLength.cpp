#include "FingerLength.h"


FingerLength::FingerLength()
{
}


FingerLength::~FingerLength()
{
}


void FingerLength::setPath(string txtPath)
{
	path = txtPath;
}


void FingerLength::displayHistogram()
{
	// proc txt
	analyzeLength(path);

	// show hist image
	int scale = 4;
	int binHeight = 256;
	int binNum = DEFAULT_MAX_FINGER_LENGTH;
	Utils::drawHistImageByHistMat(hist, scale, binHeight, binNum, "length");

	//ofstream outfileX("genLen.txt");
	//for (int i = 0; i < DEFAULT_MAX_FINGER_LENGTH; i++){
	//	outfileX << hist.at<int>(0, i) << endl;
	//}
}

//**********
// private methods as follows
//**********

void FingerLength::initHistMat()
{
	Mat mat(1, DEFAULT_MAX_FINGER_LENGTH, CV_32SC1, Scalar(0));
	hist = mat;
}


void FingerLength::analyzeLength(string path)
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
		double e2dis = sqrt(dx*dx + dy*dy);

		if (e2dis < DEFAULT_MAX_FINGER_LENGTH)
			hist.at<int>(0, (int)e2dis)++;
		else
			qDebug() << "Error finger length" << e2dis;
	}

	infile.close();

}

