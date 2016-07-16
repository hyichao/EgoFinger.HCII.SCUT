#pragma once

#include "qlabel.h"
#include "qevent.h"
#include "qpainter.h"
#include "common.h"
class ImageWidget :
	public QLabel
{
public:
	ImageWidget();
	~ImageWidget();

	bool isOn;

protected:
	void mouseMoveEvent(QMouseEvent *e);
	void paintEvent(QPaintEvent *e);

private:
	int mouseX;
	int mouseY;
};

