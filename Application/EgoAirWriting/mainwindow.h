#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "common.h"
#include "functions.h"
#include "argmanager.h"
#include "imageprocessor.h"
#include "statuscontroll.h"
#include "writing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initWithArgv(int argc, char** argv);
    void loopForward(bool isAirWriting);
    void updateView();
    void loadGestureImages();

protected slots:
    void on_writingButton_clicked();
    void on_trackingButton_clicked();
    void on_homeButton_clicked();
    void on_quitButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;

    int argc;
    char** argv;

    QImage gestureImage[6];
 private:
    ArgManager manager;
    ImageProcessor processor;
    StatusControll controll;
    Writing writing;

private:
    void updateImageLabel(Mat img);
    void updateTextLabel(string str);
    void updateGestureLabel(GesStatus status);
    void updateCandidateLabel(string cdds);
    void updateCandidateLabelColor(int pos);

    void displayMat(Mat img);
};

#endif // MAINWINDOW_H
