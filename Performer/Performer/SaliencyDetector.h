#pragma once
#include "PathManager.h"

class SaliencyDetector
{
public:
	SaliencyDetector();
	~SaliencyDetector();

public:
	void displaySaliencySequence(QString diffImgDir);

private:
	Mat frameDiffImg;			// 帧差图 作为 输入
	Mat imgGray;				// 灰度图
	Mat hist;					// 灰度直方图
	Mat colorDiffMap, distMap;	// 灰度表，帧差表
	int order;					// 帧差的阶数

	void initMaps();
	void initHistogram();

	void setColorDiffMap();
	void setDistMap();

	void showHistogram();
	Mat  getDistMap();
	
};
