#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

void Utils::drawHistImageByHistMat(Mat hist, int scale, int binHeight, int binNum, string name)
{
	// find out the maximum number in hist
	double maxVal = 0;
	for (int i = 0; i < hist.rows; i++)
		for (int j = 0; j < hist.cols; j++)
			maxVal = maxVal < hist.at<float>(i, j) ? hist.at<float>(i, j) : maxVal;
	qDebug() << "Max Value = " << maxVal;

	Mat histImage = Mat::zeros(binHeight, binNum*scale, CV_8UC3);
	for (int i = 0; i<binNum; i++)
	{
		float binVal = hist.at<float>(i);

		int intensity = round(binVal*binHeight / maxVal);  //comparative height in image

		rectangle(histImage, 
			Point(i*scale, binHeight - 1),
			Point((i + 1)*scale - 1, binHeight - intensity),
			CV_RGB(255, 255, 255));
	}

	imshow(name, histImage);
}


void Utils::writeHistMatIntoTxt(Mat hist, string filePath, string uuid)
{
	ofstream outfile(filePath.c_str(), ios::out);
	if (!outfile){
		cerr << "file could not be open." << endl;
		abort();
	}

	for (int i = 0; i < hist.rows; i++)
	{
		for (int j = 0; j < hist.cols; j++)
		{
			outfile << hist.at<float>(i,j) << ",";
		}
		outfile << endl;
	}
}

int Utils::findOutMaxIn32BitMat(Mat mat)
{
	int max = 0;
	for (int n = 0; n < mat.rows; n++)
	{
		int* p = mat.ptr<int>(n);
		for (int m = 0; m < mat.cols; m++)
			max = p[m] > max ? p[m] : max;
	}
	return max;
}

int Utils::findOutMaxIn8BitMat(Mat mat)
{
	int max = 0;
	for (int n = 0; n < mat.rows; n++)
	{
		uchar* p = mat.ptr<uchar>(n);
		for (int m = 0; m < mat.cols; m++)
			max = p[m] > max ? p[m] : max;
	}
	return max;
}

double Utils::calcAverage(double data[], int num)
{
	double avg = 0;
	for (int i = 0; i < num; i++)
	{
		avg += data[i];
	}
	avg /= num;
	return avg;
}

string Utils::stringFromInt(int num)
{
	char str[16];
	itoa(num, str, 10);
	return str;
}

double Utils::calcDistance(int x1, int y1, int x2, int y2)
{
	double res = 0;
	int dx = (x1 - x2);
	int dy = (y1 - y2);
	res = sqrt(dx*dx + dy*dy);
	return res;
}


Mat Utils::calcHistogram(const Mat &image)
{

	int histSize[1];
	float hranges[2];
	const float *ranges[1];

	histSize[0] = 256;		//seperate into 255 bins, 0 excluded 
	hranges[0] = 0.0;		//min px val
	hranges[1] = 255.0;		//max px val
	ranges[0] = hranges;	//px val range

	Mat hist;
	calcHist(&image,
		1,			//image num
		0,			//channels (0 as default)
		Mat(),		//no mask
		hist,		//output
		1,			//1 dimension histogram
		histSize,	//bin number
		ranges		//pixel range
		);
	return hist;
}