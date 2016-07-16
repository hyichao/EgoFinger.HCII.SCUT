#ifndef PERFORMER_H
#define PERFORMER_H

#include <QtWidgets/QMainWindow>
#include "ui_performer.h"

#include "PathManager.h"

#include "ColorDistribution.h"
#include "BoxDistribution.h"
#include "MovementDetector.h"
#include "FingerLength.h"
#include "PointingDirection.h"
#include "FrameDifference.h"
#include "SaliencyDetector.h"

#include "ErrorAnalyzer.h"

class Performer : public QMainWindow
{
	Q_OBJECT

public:
	Performer(QWidget *parent = 0);
	~Performer();
	
private slots:

	void on_colorDistButt_clicked();
	void on_posDistButt_clicked();
	void on_moveDistButt_clicked();
	void on_frameDiffButt_clicked();
	void on_saliencyButt_clicked();
	void on_fingerLengthButt_clicked();
	void on_pointingDirButt_clicked();

	void on_dirButt_clicked();
	void on_fileButt_clicked();

	void on_errorButt_clicked();

private:
	Ui::PerformerClass ui;

	PathManager pathManager;

public:
	void displayBGRMat(Mat mat);
};

#endif // PERFORMER_H
