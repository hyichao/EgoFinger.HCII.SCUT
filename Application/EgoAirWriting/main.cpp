#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("第一视角空中手写");
//    w.setWindowOpacity(0.618);

//    w.setWindowFlags(Qt::FramelessWindowHint);

    w.setObjectName("mainWindow");
    w.setStyleSheet("background-color:black;");

    w.setAttribute(Qt::WA_TranslucentBackground);
    w.initWithArgv(argc,argv);
    w.show();

    return a.exec();
}
  
