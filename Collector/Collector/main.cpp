#include "collector.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Collector w;
	w.show();
	return a.exec();
}
