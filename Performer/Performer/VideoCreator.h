#pragma once
#include "common.h"

class VideoCreator
{
public:
	VideoCreator();
	~VideoCreator();

private:
	double imgWidth, imgHeight, fps;

public:
	int writeVideo(string targetDir);

};

