/********************************************************************************
** Form generated from reading UI file 'performer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERFORMER_H
#define UI_PERFORMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PerformerClass
{
public:
    QWidget *centralWidget;
    QPushButton *frameDiffButt;
    QPushButton *colorDistButt;
    QPushButton *posDistButt;
    QPushButton *moveDistButt;
    QLabel *colorLabel;
    QPushButton *dirButt;
    QPushButton *fileButt;
    QLabel *dirLabel;
    QLabel *txtLabel;
    QComboBox *typeComboBox;
    QComboBox *spaceComboBox;
    QLabel *PathLabel;
    QLabel *label_2;
    QLabel *colorLabel_2;
    QLabel *colorLabel_3;
    QPushButton *saliencyButt;
    QComboBox *orderComboBox;
    QComboBox *pointComboBox;
    QPushButton *errorButt;
    QPushButton *fingerLengthButt;
    QPushButton *pointingDirButt;

    void setupUi(QMainWindow *PerformerClass)
    {
        if (PerformerClass->objectName().isEmpty())
            PerformerClass->setObjectName(QStringLiteral("PerformerClass"));
        PerformerClass->setWindowModality(Qt::ApplicationModal);
        PerformerClass->resize(1129, 308);
        PerformerClass->setStyleSheet(QStringLiteral("color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 0, 0, 255), stop:0.05 rgba(14, 8, 73, 255), stop:0.36 rgba(28, 17, 145, 255), stop:0.6 rgba(126, 14, 81, 255), stop:0.75 rgba(234, 11, 11, 255), stop:0.79 rgba(244, 70, 5, 255), stop:0.86 rgba(255, 136, 0, 255), stop:0.935 rgba(239, 236, 55, 255));"));
        centralWidget = new QWidget(PerformerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frameDiffButt = new QPushButton(centralWidget);
        frameDiffButt->setObjectName(QStringLiteral("frameDiffButt"));
        frameDiffButt->setGeometry(QRect(880, 160, 231, 31));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        frameDiffButt->setFont(font);
        colorDistButt = new QPushButton(centralWidget);
        colorDistButt->setObjectName(QStringLiteral("colorDistButt"));
        colorDistButt->setGeometry(QRect(20, 160, 241, 31));
        colorDistButt->setFont(font);
        posDistButt = new QPushButton(centralWidget);
        posDistButt->setObjectName(QStringLiteral("posDistButt"));
        posDistButt->setGeometry(QRect(300, 160, 261, 31));
        posDistButt->setFont(font);
        moveDistButt = new QPushButton(centralWidget);
        moveDistButt->setObjectName(QStringLiteral("moveDistButt"));
        moveDistButt->setGeometry(QRect(300, 210, 261, 31));
        moveDistButt->setFont(font);
        colorLabel = new QLabel(centralWidget);
        colorLabel->setObjectName(QStringLiteral("colorLabel"));
        colorLabel->setGeometry(QRect(40, 110, 201, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        colorLabel->setFont(font1);
        colorLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        colorLabel->setAlignment(Qt::AlignCenter);
        dirButt = new QPushButton(centralWidget);
        dirButt->setObjectName(QStringLiteral("dirButt"));
        dirButt->setGeometry(QRect(220, 10, 161, 40));
        dirButt->setFont(font);
        fileButt = new QPushButton(centralWidget);
        fileButt->setObjectName(QStringLiteral("fileButt"));
        fileButt->setGeometry(QRect(220, 50, 161, 40));
        fileButt->setFont(font);
        dirLabel = new QLabel(centralWidget);
        dirLabel->setObjectName(QStringLiteral("dirLabel"));
        dirLabel->setGeometry(QRect(400, 10, 411, 41));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(20);
        font2.setItalic(true);
        dirLabel->setFont(font2);
        dirLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        txtLabel = new QLabel(centralWidget);
        txtLabel->setObjectName(QStringLiteral("txtLabel"));
        txtLabel->setGeometry(QRect(400, 54, 411, 41));
        txtLabel->setFont(font2);
        txtLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        typeComboBox = new QComboBox(centralWidget);
        typeComboBox->setObjectName(QStringLiteral("typeComboBox"));
        typeComboBox->setGeometry(QRect(30, 200, 141, 31));
        QFont font3;
        font3.setPointSize(15);
        typeComboBox->setFont(font3);
        spaceComboBox = new QComboBox(centralWidget);
        spaceComboBox->setObjectName(QStringLiteral("spaceComboBox"));
        spaceComboBox->setGeometry(QRect(190, 200, 71, 31));
        spaceComboBox->setFont(font3);
        PathLabel = new QLabel(centralWidget);
        PathLabel->setObjectName(QStringLiteral("PathLabel"));
        PathLabel->setGeometry(QRect(20, 20, 161, 71));
        PathLabel->setFont(font);
        PathLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        PathLabel->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(870, 110, 231, 31));
        label_2->setFont(font1);
        label_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);
        colorLabel_2 = new QLabel(centralWidget);
        colorLabel_2->setObjectName(QStringLiteral("colorLabel_2"));
        colorLabel_2->setGeometry(QRect(640, 110, 161, 31));
        colorLabel_2->setFont(font1);
        colorLabel_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        colorLabel_2->setAlignment(Qt::AlignCenter);
        colorLabel_3 = new QLabel(centralWidget);
        colorLabel_3->setObjectName(QStringLiteral("colorLabel_3"));
        colorLabel_3->setGeometry(QRect(320, 110, 161, 31));
        colorLabel_3->setFont(font1);
        colorLabel_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        colorLabel_3->setAlignment(Qt::AlignCenter);
        saliencyButt = new QPushButton(centralWidget);
        saliencyButt->setObjectName(QStringLiteral("saliencyButt"));
        saliencyButt->setGeometry(QRect(880, 210, 231, 31));
        saliencyButt->setFont(font);
        orderComboBox = new QComboBox(centralWidget);
        orderComboBox->setObjectName(QStringLiteral("orderComboBox"));
        orderComboBox->setGeometry(QRect(930, 250, 141, 31));
        orderComboBox->setFont(font3);
        pointComboBox = new QComboBox(centralWidget);
        pointComboBox->setObjectName(QStringLiteral("pointComboBox"));
        pointComboBox->setGeometry(QRect(320, 250, 211, 31));
        pointComboBox->setFont(font3);
        errorButt = new QPushButton(centralWidget);
        errorButt->setObjectName(QStringLiteral("errorButt"));
        errorButt->setGeometry(QRect(840, 30, 271, 41));
        QFont font4;
        font4.setPointSize(20);
        errorButt->setFont(font4);
        fingerLengthButt = new QPushButton(centralWidget);
        fingerLengthButt->setObjectName(QStringLiteral("fingerLengthButt"));
        fingerLengthButt->setGeometry(QRect(610, 160, 241, 31));
        fingerLengthButt->setFont(font);
        pointingDirButt = new QPushButton(centralWidget);
        pointingDirButt->setObjectName(QStringLiteral("pointingDirButt"));
        pointingDirButt->setGeometry(QRect(610, 210, 241, 31));
        pointingDirButt->setFont(font);
        PerformerClass->setCentralWidget(centralWidget);

        retranslateUi(PerformerClass);

        QMetaObject::connectSlotsByName(PerformerClass);
    } // setupUi

    void retranslateUi(QMainWindow *PerformerClass)
    {
        PerformerClass->setWindowTitle(QApplication::translate("PerformerClass", "Performer", 0));
        frameDiffButt->setText(QApplication::translate("PerformerClass", "Frame Difference", 0));
        colorDistButt->setText(QApplication::translate("PerformerClass", "Color Distribution", 0));
        posDistButt->setText(QApplication::translate("PerformerClass", "Position Distribution", 0));
        moveDistButt->setText(QApplication::translate("PerformerClass", "Movement Distribution", 0));
        colorLabel->setText(QApplication::translate("PerformerClass", "Color Module", 0));
        dirButt->setText(QApplication::translate("PerformerClass", "Directory", 0));
        fileButt->setText(QApplication::translate("PerformerClass", "Txt Path", 0));
        dirLabel->setText(QApplication::translate("PerformerClass", "Directory of Images", 0));
        txtLabel->setText(QApplication::translate("PerformerClass", "Path of Txt", 0));
        typeComboBox->clear();
        typeComboBox->insertItems(0, QStringList()
         << QApplication::translate("PerformerClass", "Full Image", 0)
         << QApplication::translate("PerformerClass", "Inside Box", 0)
         << QApplication::translate("PerformerClass", "Outside Box", 0)
        );
        spaceComboBox->clear();
        spaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("PerformerClass", "BGR", 0)
         << QApplication::translate("PerformerClass", "HSV", 0)
         << QApplication::translate("PerformerClass", "YCrCb", 0)
         << QApplication::translate("PerformerClass", "Lab", 0)
        );
        spaceComboBox->setCurrentText(QApplication::translate("PerformerClass", "BGR", 0));
        PathLabel->setText(QApplication::translate("PerformerClass", "Path Selection ", 0));
        label_2->setText(QApplication::translate("PerformerClass", "Frame Difference Module", 0));
        colorLabel_2->setText(QApplication::translate("PerformerClass", "Shape Module", 0));
        colorLabel_3->setText(QApplication::translate("PerformerClass", "Position Module", 0));
        saliencyButt->setText(QApplication::translate("PerformerClass", "Saliency", 0));
        orderComboBox->clear();
        orderComboBox->insertItems(0, QStringList()
         << QApplication::translate("PerformerClass", "first order", 0)
         << QApplication::translate("PerformerClass", "second order", 0)
         << QApplication::translate("PerformerClass", "third order", 0)
        );
        pointComboBox->clear();
        pointComboBox->insertItems(0, QStringList()
         << QApplication::translate("PerformerClass", "BoundingBoxTopLeft", 0)
         << QApplication::translate("PerformerClass", "BoundingBoxBottomRight", 0)
         << QApplication::translate("PerformerClass", "IndexFingertip", 0)
         << QApplication::translate("PerformerClass", "IndexJoint", 0)
         << QApplication::translate("PerformerClass", "TailJoint", 0)
         << QApplication::translate("PerformerClass", "ThumbTip", 0)
         << QApplication::translate("PerformerClass", "ThumbJoint", 0)
        );
        errorButt->setText(QApplication::translate("PerformerClass", "Error Analysis", 0));
        fingerLengthButt->setText(QApplication::translate("PerformerClass", "Finger Length", 0));
        pointingDirButt->setText(QApplication::translate("PerformerClass", "Pointing Direction", 0));
    } // retranslateUi

};

namespace Ui {
    class PerformerClass: public Ui_PerformerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERFORMER_H
