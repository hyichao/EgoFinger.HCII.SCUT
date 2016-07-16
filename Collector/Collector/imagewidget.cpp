#include "imagewidget.h"


ImageWidget::ImageWidget()
{
	this->setMouseTracking(true);
}


ImageWidget::~ImageWidget()
{
}

void ImageWidget::mouseMoveEvent(QMouseEvent *e)
{
	mouseX = e->x();
	mouseY = e->y();
	update();
}

void ImageWidget::paintEvent(QPaintEvent *e)
{
	if (!isOn)
		return;

	QPainter p(this);
	QPen pen = p.pen();
	pen.setWidth(0.5);
	p.setPen(pen);
	p.setRenderHint(QPainter::Antialiasing, true);

	p.drawLine(mouseX, 0, mouseX, this->height());
	p.drawLine(0, mouseY, this->width(), mouseY);
}