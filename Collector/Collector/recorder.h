#ifndef RECORDER_H
#define RECORDER_H

#include "common.h"

#include <QFile>
#include <QStringList>

class Recorder
{
public:
	Recorder();
	~Recorder();

public:

	QString outFilePath;
	QFile outFile;

	QStringList strList;

public:

	void initFileStream(QString currentDir);
	void appendStringList(QString fileName, vector<float> params);
	void writeDataFile();

	static void writeLog(QString str);

};

#endif // RECORDER_H
