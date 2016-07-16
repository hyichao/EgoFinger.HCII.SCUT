#include "performer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Performer w;

	w.setWindowTitle("Dataset Performance");
	w.setWindowOpacity(0.618);
	//w.setWindowFlags(Qt::FramelessWindowHint);
	w.setAttribute(Qt::WA_TranslucentBackground);

	w.show();
	return a.exec();
}
