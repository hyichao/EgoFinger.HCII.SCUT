#include "ColorDistribution.h"


ColorDistribution::ColorDistribution()
{
}


ColorDistribution::~ColorDistribution()
{
}

void ColorDistribution::init(string dir, string inTxtPath,	DistributionType inType, ColorSpace inColorSpace)
{
	imageDir = dir;
	inputTxtPath = inTxtPath;

	type = inType;
	colorSpace = inColorSpace;

}

void ColorDistribution::calcHistogram()
{
	ifstream infile(inputTxtPath, ios::in);
	if (!infile)
	{
		qDebug() << "Error! Empty File!! Pls Check File Path!";
		abort();
	}

	int index = 0;
	int limitNum = 200;		// FIXME£ºfor reducing time
	while (	infile >> pictureName
		>> boxCoord[0] >> boxCoord[1] >> boxCoord[2] >> boxCoord[3]
		>> pointCoord[0] >> pointCoord[1] >> pointCoord[2] >> pointCoord[3] >> pointCoord[4] >> pointCoord[5] >>
		pointCoord[6] >> pointCoord[7] >> pointCoord[8] >> pointCoord[9])
	{
		addUpHist();

		index++;
		if (index > limitNum)
			break;
	}
	histX /= index;
	histY /= index;
	histZ /= index;

	infile.close();
}


/*
read image from path, return mat
*/
Mat ColorDistribution::readImage(string imageName)
{
	string inPath;
	inPath = imageDir + "/" + imageName;		
	Mat picture = imread(inPath);
	return picture;
}

/*
type£ºThe color histogram module include: Inside BoundingBox£¬Outside BoundingBox£¬Full Image;
colorSpace£ºThe color space include: BGR, HSV, YCrCb, Lab
*/
void ColorDistribution::addUpHist()
{
	//read in new image while looping, convert color space
	Mat src = readImage(pictureName);
	Mat dst;
	if (colorSpace == SPACE_BGR)
		src.copyTo(dst);
	if (colorSpace == SPACE_HSV)		
		cvtColor(src, dst, COLOR_BGR2HSV_FULL);
	if (colorSpace == SPACE_YCrCb)	
		cvtColor(src, dst, COLOR_BGR2YCrCb);
	if (colorSpace == SPACE_Lab)
		cvtColor(src, dst, COLOR_BGR2Lab);

	//seperate into 3 channels
	vector<Mat> planes;					
	split(dst, planes);	

	// calc bounding box coords 
	int topLeftX = int(IMAGE_DEFAULT_WIDTH * boxCoord[0]);
	int topLeftY = int(IMAGE_DEFAULT_HEIGHT * boxCoord[1]);
	int row = int(IMAGE_DEFAULT_HEIGHT * (boxCoord[3] - boxCoord[1]));
	int col = int(IMAGE_DEFAULT_WIDTH * (boxCoord[2] - boxCoord[0]));

	// make roi with bounding box
	Mat roiX = planes[0](Rect(topLeftX, topLeftY, col, row));
	Mat roiY = planes[1](Rect(topLeftX, topLeftY, col, row));
	Mat roiZ = planes[2](Rect(topLeftX, topLeftY, col, row));

	// calc hist
	Mat newHistX, newHistY, newHistZ;
	Mat newBoxHistX, newBoxHistY, newBoxHistZ;
	newHistX = Utils::calcHistogram(planes[0]);	
	newHistY = Utils::calcHistogram(planes[1]);
	newHistZ = Utils::calcHistogram(planes[2]);
	newBoxHistX = Utils::calcHistogram(roiX);
	newBoxHistY = Utils::calcHistogram(roiY);
	newBoxHistZ = Utils::calcHistogram(roiZ);

	// add up hist by looping
	if (type == WHOLE_IMAGE)
	{
		histX = (histX.dims == 0) ? newHistX : (histX + newHistX);
		histY = (histY.dims == 0) ? newHistY : (histY + newHistY);
		histZ = (histZ.dims == 0) ? newHistZ : (histZ + newHistZ);
	}
	if (type == INSIDE_BOUNDING_BOX)
	{
		histX = (histX.dims == 0) ? newBoxHistX : histX + newBoxHistX;
		histY = (histY.dims == 0) ? newBoxHistY : histY + newBoxHistY;
		histZ = (histZ.dims == 0) ? newBoxHistZ : histZ + newBoxHistZ;
	}
	if (type == OUTSIDE_BOUNDING_BOX)
	{
		histX = (histX.dims == 0) ? (newHistX - newBoxHistX) : histX + (newHistX - newBoxHistX);
		histY = (histY.dims == 0) ? (newHistY - newBoxHistY) : histY + (newHistY - newBoxHistY);
		histZ = (histZ.dims == 0) ? (newHistZ - newBoxHistZ) : histZ + (newHistZ - newBoxHistZ);
	}
	return;
}

void ColorDistribution::showHistogram()
{
	// show window names ..
	string histTypeName;	
	switch (type)
	{
	case INSIDE_BOUNDING_BOX:histTypeName = "(in bounding box)"; break;
	case OUTSIDE_BOUNDING_BOX:histTypeName = "(out bounding box)"; break;
	case WHOLE_IMAGE:histTypeName = "(whole image)"; break;
	}

	string colorSpaceName[3];
	switch (colorSpace)
	{
	case SPACE_BGR:
		colorSpaceName[0] = "B";colorSpaceName[1] = "G";colorSpaceName[2] = "R";break;
	case SPACE_HSV:
		colorSpaceName[0] = "H";colorSpaceName[1] = "S";colorSpaceName[2] = "V";break;
	case SPACE_YCrCb:
		colorSpaceName[0] = "Y";colorSpaceName[1] = "Cr";colorSpaceName[2] = "Cb";break;
	case SPACE_Lab:
		colorSpaceName[0] = "L";colorSpaceName[1] = "a";colorSpaceName[2] = "b";break;
	default:
		break;
	}
	ofstream outfileX("genX.txt");
	for (int i = 0; i < 255; i++){
		outfileX << histX.at<float>(i, 0) << endl;
	}

	ofstream outfileY("genY.txt");
	for (int i = 0; i < 255; i++){
		outfileY << histY.at<float>(i, 0) << endl;
	}

	ofstream outfileZ("genZ.txt");
	for (int i = 0; i < 255; i++){
		outfileZ << histZ.at<float>(i, 0) << endl;
	}

	const int scale = 3;
	const int binHeight = 512;
	const int binNum = 256;
	string nameX = "channel " + colorSpaceName[0] + " + " + histTypeName;
	string nameY = "channel " + colorSpaceName[1] + " + " + histTypeName;
	string nameZ = "channel " + colorSpaceName[2] + " + " + histTypeName;
	Utils::drawHistImageByHistMat(histX, scale, binHeight, binNum, nameX);
	Utils::drawHistImageByHistMat(histY, scale, binHeight, binNum, nameY);
	Utils::drawHistImageByHistMat(histZ, scale, binHeight, binNum, nameZ);
}
