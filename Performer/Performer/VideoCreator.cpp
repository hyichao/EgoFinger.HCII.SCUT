#include "VideoCreator.h"


VideoCreator::VideoCreator()
{
	fps = DEFAULT_FPS;					//帧率
	imgWidth = IMAGE_DEFAULT_WIDTH;		//图片格式统一
	imgHeight = IMAGE_DEFAULT_HEIGHT;	//图片格式统一
}


VideoCreator::~VideoCreator()
{
}


/*
此处需要优化，应该读入一个文件夹之后直接按照顺序就读入，不应该要求固定的文件名格式
目前做法：目标文件夹必须包含连续数字从0开始的png图片。
*/
int VideoCreator::writeVideo(string targetDir)
{
	Size frameSize(static_cast<int>(imgWidth), static_cast<int>(imgHeight));
	VideoWriter videoWriter("FrameDifference.avi", CV_FOURCC('D', 'I', 'V', 'X'), fps, frameSize, 1);
	if (!videoWriter.isOpened())
	{
		qDebug() << "Fail to Initialize Video Writer, Pls Check Frame Size or Decoder！" << endl;
		return -1;
	}

	int i = 0;
	while (true)
	{
		string targetPath = targetDir + "/" + i + ".png";
		Mat img = imread(targetPath);
		if (img.empty())
		{
			qDebug()<< "Read Image Ends" << endl;
			break;
		}
		videoWriter.write(img);
		qDebug() << "写入第" << i << "张帧成功" << endl;
		i++;
	}
}

