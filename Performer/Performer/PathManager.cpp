#include "PathManager.h"
#include <direct.h>


PathManager::PathManager()
{
	setTargetDir();
	_mkdir( targetDir.toStdString().data() );			//make "gen" dir in exe dir
}


PathManager::~PathManager()
{
}

void PathManager::setDir(QString fileDir)
{
	dir = fileDir;
}


void PathManager::setFile(QString filePath)
{
	file = filePath;
}

QString PathManager::getDir()
{
	return dir;
}

QString PathManager::getFile()
{
	return file;
}

void PathManager::setTargetDir()
{
	QDir dir;
	targetDir = dir.currentPath()+"/gen";
}

QString PathManager::getTargetDir()
{
	return targetDir;
}