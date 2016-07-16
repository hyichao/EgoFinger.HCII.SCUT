#pragma once
#include "common.h"

class PathManager
{

private:
	QString dir;		// image directory
	QString file;		// txt file path

	QString targetDir;	// output target dir

public:
	PathManager();
	~PathManager();

	QString getDir();
	void setDir(QString fileDir);

	QString getFile();
	void setFile(QString filePath);

	void setTargetDir();
	QString getTargetDir();
};

