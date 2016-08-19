#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <QtWidgets/QMainWindow>
#include "ui_collector.h"

#include "common.h"

#include <QDir>
#include <QShortCut>
#include <QMouseEvent>
#include <QFileDialog>

//class to process mat
#include "processor.h"
//class to record data
#include "recorder.h"
//class to create databse
#include "database.h"

#include "imagewidget.h"
#include "qlayout.h"

class Collector : public QMainWindow
{
	Q_OBJECT

public:
	Collector(QWidget *parent = 0);
	~Collector();

private:
	Ui::CollectorClass ui;
	ImageWidget *imgWidget;

	//core identification of image in path name
	int index;
	int minCount;
	int maxCount;

	QString targetDir;
	QString targetBaseName;

	QString currentImageName;

	//mat processor
	Processor proc;
	//sqlite db
	Database db;


private slots:
	void on_videoButt_clicked();

	void on_selectButt_clicked();

	void on_startButt_clicked();

	void on_endButt_clicked();

	void on_lastButt_clicked();

	void on_nextButt_clicked();


protected:
	void mousePressEvent(QMouseEvent *e);
	
public:
	//auxilary function
	void updateWithIndex(int index);
	void recordDataIntoDb();

	//display funcion of ui
	void displayMat(Mat img);
	void displayData();

	
};

#endif // COLLECTOR_H
