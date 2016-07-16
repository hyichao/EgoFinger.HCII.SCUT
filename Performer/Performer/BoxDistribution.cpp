#include "BoxDistribution.h"


BoxDistribution::BoxDistribution()
{
}


BoxDistribution::~BoxDistribution()
{
}


//******************
// Usage£º
// 1. send in txt path
// 2. calculate and show frequency image
//******************
void BoxDistribution::showFrequencyMat(string txtPath){

	ifstream infile(txtPath.c_str(), ios::in);
	infile.seekg(0, ios::beg);
	if (!infile){
		cerr << "file could not be open." << endl;
		abort();
	}

	initCountingMat();
	initFrequencyMat();

	string filename;
	double data[DEFAULT_COORD_NUM];
	while (infile >> filename >> data[0] >> data[1] >> data[2] >> data[3]
		>> data[4] >> data[5] >> data[6] >> data[7] >> data[8]
		>> data[9] >> data[10] >> data[11] >> data[12] >> data[13])
	{
		addUpCountingMat(data);
	}
	infile.close();

	normalizeCountingMat(data);

	imshow("BoundingBox Distribution", frequancyMat);
}

void BoxDistribution::addUpCountingMat(double data[14])
{
	int tlx = data[0] * IMAGE_DEFAULT_WIDTH;
	int brx = data[2] * IMAGE_DEFAULT_WIDTH;
	int tly = data[1] * IMAGE_DEFAULT_HEIGHT;
	int bry = data[3] * IMAGE_DEFAULT_HEIGHT;

	// iterate through counting mat and add one if inside of bounding box
	for (int n = tly; n < bry; n++)			
	{
		int* p = countingMat.ptr<int>(n);
		for (int m = tlx; m < brx; m++)		
			p[m]++;
	}
}

void BoxDistribution::normalizeCountingMat(double data[14])
{
	int max = Utils::findOutMaxIn32BitMat(countingMat);
	
	//normalize to uchar 0-255
	int rows = countingMat.rows;
	int cols = countingMat.cols;
	for (int n = 0; n < rows; n++)
	{
		int* p = countingMat.ptr<int>(n);
		uchar* q = frequancyMat.ptr<uchar>(n);
		for (int m = 0; m < cols; m++)
		{
			q[m] = p[m] * 255 / max;
		}
	}
}


void BoxDistribution::initCountingMat()
{
	Mat img(IMAGE_DEFAULT_HEIGHT, IMAGE_DEFAULT_WIDTH, CV_32SC1, Scalar(0));
	img.setTo(0);
	countingMat = img;
}

void BoxDistribution::initFrequencyMat(){
	Mat img(IMAGE_DEFAULT_HEIGHT, IMAGE_DEFAULT_WIDTH, CV_8UC1, Scalar(0));
	img.setTo(0);
	frequancyMat = img;
}

