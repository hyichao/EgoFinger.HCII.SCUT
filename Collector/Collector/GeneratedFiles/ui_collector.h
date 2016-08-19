/********************************************************************************
** Form generated from reading UI file 'collector.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLLECTOR_H
#define UI_COLLECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CollectorClass
{
public:
    QWidget *centralWidget;
    QLabel *imageLabel;
    QPushButton *startButt;
    QPushButton *endButt;
    QPushButton *lastButt;
    QPushButton *nextButt;
    QLabel *pathLabel;
    QLabel *fileNameLabel;
    QLabel *tlLabel;
    QLabel *brLabel;
    QLabel *iftLabel;
    QLabel *ifjLabel;
    QPushButton *videoButt;
    QPushButton *selectButt;
    QLineEdit *lineEdit;
    QLabel *label;
    QFrame *line;
    QFrame *line_2;
    QLabel *tfjLabel;
    QFrame *line_3;
    QLabel *bjLabel;
    QLabel *btLabel;
    QLabel *rLabel;
    QLabel *rfjLabel;
    QLabel *mftLabel;
    QLabel *rftLabel;
    QLabel *tftLabel_l;
    QLabel *mftLabel_l;
    QLabel *iftLabel_l;
    QLabel *tfjLabel_2;
    QLabel *mfjLabel;
    QLabel *bjLabel_2;
    QLabel *tftLabel;
    QLabel *rftLabel_l;
    QLabel *tlLabel_2;
    QLabel *bjLabel_l;
    QLabel *tlLabel_l;
    QLabel *ifjLabel_l;
    QLabel *tfjLabel_l;
    QLabel *rfjLabel_l;
    QLabel *lLabel;
    QLabel *btLabel_2;
    QLabel *iftLabel_2;
    QLabel *brLabel_2;
    QLabel *btLabel_l;
    QLabel *brLabel_l;
    QLabel *mfjLabel_l;
    QLabel *ifjLabel_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CollectorClass)
    {
        if (CollectorClass->objectName().isEmpty())
            CollectorClass->setObjectName(QStringLiteral("CollectorClass"));
        CollectorClass->resize(1394, 600);
        centralWidget = new QWidget(CollectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setGeometry(QRect(50, 50, 640, 480));
        startButt = new QPushButton(centralWidget);
        startButt->setObjectName(QStringLiteral("startButt"));
        startButt->setGeometry(QRect(810, 150, 75, 23));
        endButt = new QPushButton(centralWidget);
        endButt->setObjectName(QStringLiteral("endButt"));
        endButt->setGeometry(QRect(740, 190, 141, 23));
        lastButt = new QPushButton(centralWidget);
        lastButt->setObjectName(QStringLiteral("lastButt"));
        lastButt->setGeometry(QRect(730, 260, 75, 23));
        nextButt = new QPushButton(centralWidget);
        nextButt->setObjectName(QStringLiteral("nextButt"));
        nextButt->setGeometry(QRect(810, 260, 75, 23));
        pathLabel = new QLabel(centralWidget);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        pathLabel->setGeometry(QRect(740, 100, 121, 20));
        fileNameLabel = new QLabel(centralWidget);
        fileNameLabel->setObjectName(QStringLiteral("fileNameLabel"));
        fileNameLabel->setGeometry(QRect(730, 310, 151, 20));
        tlLabel = new QLabel(centralWidget);
        tlLabel->setObjectName(QStringLiteral("tlLabel"));
        tlLabel->setGeometry(QRect(750, 370, 121, 20));
        brLabel = new QLabel(centralWidget);
        brLabel->setObjectName(QStringLiteral("brLabel"));
        brLabel->setGeometry(QRect(750, 390, 121, 20));
        iftLabel = new QLabel(centralWidget);
        iftLabel->setObjectName(QStringLiteral("iftLabel"));
        iftLabel->setGeometry(QRect(750, 410, 121, 20));
        ifjLabel = new QLabel(centralWidget);
        ifjLabel->setObjectName(QStringLiteral("ifjLabel"));
        ifjLabel->setGeometry(QRect(750, 430, 121, 20));
        videoButt = new QPushButton(centralWidget);
        videoButt->setObjectName(QStringLiteral("videoButt"));
        videoButt->setGeometry(QRect(740, 20, 121, 23));
        selectButt = new QPushButton(centralWidget);
        selectButt->setObjectName(QStringLiteral("selectButt"));
        selectButt->setGeometry(QRect(740, 60, 121, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(762, 150, 41, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(740, 150, 16, 20));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(730, 120, 161, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(730, 230, 151, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        tfjLabel = new QLabel(centralWidget);
        tfjLabel->setObjectName(QStringLiteral("tfjLabel"));
        tfjLabel->setGeometry(QRect(750, 450, 121, 20));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(730, 340, 151, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        bjLabel = new QLabel(centralWidget);
        bjLabel->setObjectName(QStringLiteral("bjLabel"));
        bjLabel->setGeometry(QRect(750, 490, 121, 20));
        btLabel = new QLabel(centralWidget);
        btLabel->setObjectName(QStringLiteral("btLabel"));
        btLabel->setGeometry(QRect(750, 470, 121, 20));
        rLabel = new QLabel(centralWidget);
        rLabel->setObjectName(QStringLiteral("rLabel"));
        rLabel->setGeometry(QRect(1220, 20, 54, 12));
        rfjLabel = new QLabel(centralWidget);
        rfjLabel->setObjectName(QStringLiteral("rfjLabel"));
        rfjLabel->setGeometry(QRect(1200, 260, 161, 16));
        mftLabel = new QLabel(centralWidget);
        mftLabel->setObjectName(QStringLiteral("mftLabel"));
        mftLabel->setGeometry(QRect(1200, 170, 161, 16));
        rftLabel = new QLabel(centralWidget);
        rftLabel->setObjectName(QStringLiteral("rftLabel"));
        rftLabel->setGeometry(QRect(1200, 230, 161, 16));
        tftLabel_l = new QLabel(centralWidget);
        tftLabel_l->setObjectName(QStringLiteral("tftLabel_l"));
        tftLabel_l->setGeometry(QRect(1020, 290, 161, 16));
        mftLabel_l = new QLabel(centralWidget);
        mftLabel_l->setObjectName(QStringLiteral("mftLabel_l"));
        mftLabel_l->setGeometry(QRect(1020, 170, 161, 16));
        iftLabel_l = new QLabel(centralWidget);
        iftLabel_l->setObjectName(QStringLiteral("iftLabel_l"));
        iftLabel_l->setGeometry(QRect(1020, 110, 161, 16));
        tfjLabel_2 = new QLabel(centralWidget);
        tfjLabel_2->setObjectName(QStringLiteral("tfjLabel_2"));
        tfjLabel_2->setGeometry(QRect(1200, 320, 161, 16));
        mfjLabel = new QLabel(centralWidget);
        mfjLabel->setObjectName(QStringLiteral("mfjLabel"));
        mfjLabel->setGeometry(QRect(1200, 200, 161, 16));
        bjLabel_2 = new QLabel(centralWidget);
        bjLabel_2->setObjectName(QStringLiteral("bjLabel_2"));
        bjLabel_2->setGeometry(QRect(1200, 380, 161, 20));
        tftLabel = new QLabel(centralWidget);
        tftLabel->setObjectName(QStringLiteral("tftLabel"));
        tftLabel->setGeometry(QRect(1200, 290, 161, 16));
        rftLabel_l = new QLabel(centralWidget);
        rftLabel_l->setObjectName(QStringLiteral("rftLabel_l"));
        rftLabel_l->setGeometry(QRect(1020, 230, 161, 16));
        tlLabel_2 = new QLabel(centralWidget);
        tlLabel_2->setObjectName(QStringLiteral("tlLabel_2"));
        tlLabel_2->setGeometry(QRect(1200, 50, 161, 16));
        bjLabel_l = new QLabel(centralWidget);
        bjLabel_l->setObjectName(QStringLiteral("bjLabel_l"));
        bjLabel_l->setGeometry(QRect(1020, 380, 161, 20));
        tlLabel_l = new QLabel(centralWidget);
        tlLabel_l->setObjectName(QStringLiteral("tlLabel_l"));
        tlLabel_l->setGeometry(QRect(1020, 50, 161, 16));
        ifjLabel_l = new QLabel(centralWidget);
        ifjLabel_l->setObjectName(QStringLiteral("ifjLabel_l"));
        ifjLabel_l->setGeometry(QRect(1020, 140, 161, 16));
        tfjLabel_l = new QLabel(centralWidget);
        tfjLabel_l->setObjectName(QStringLiteral("tfjLabel_l"));
        tfjLabel_l->setGeometry(QRect(1020, 320, 161, 16));
        rfjLabel_l = new QLabel(centralWidget);
        rfjLabel_l->setObjectName(QStringLiteral("rfjLabel_l"));
        rfjLabel_l->setGeometry(QRect(1020, 260, 161, 16));
        lLabel = new QLabel(centralWidget);
        lLabel->setObjectName(QStringLiteral("lLabel"));
        lLabel->setGeometry(QRect(1040, 20, 54, 12));
        btLabel_2 = new QLabel(centralWidget);
        btLabel_2->setObjectName(QStringLiteral("btLabel_2"));
        btLabel_2->setGeometry(QRect(1200, 350, 161, 20));
        iftLabel_2 = new QLabel(centralWidget);
        iftLabel_2->setObjectName(QStringLiteral("iftLabel_2"));
        iftLabel_2->setGeometry(QRect(1200, 110, 161, 16));
        brLabel_2 = new QLabel(centralWidget);
        brLabel_2->setObjectName(QStringLiteral("brLabel_2"));
        brLabel_2->setGeometry(QRect(1200, 80, 161, 16));
        btLabel_l = new QLabel(centralWidget);
        btLabel_l->setObjectName(QStringLiteral("btLabel_l"));
        btLabel_l->setGeometry(QRect(1020, 350, 161, 20));
        brLabel_l = new QLabel(centralWidget);
        brLabel_l->setObjectName(QStringLiteral("brLabel_l"));
        brLabel_l->setGeometry(QRect(1020, 80, 161, 16));
        mfjLabel_l = new QLabel(centralWidget);
        mfjLabel_l->setObjectName(QStringLiteral("mfjLabel_l"));
        mfjLabel_l->setGeometry(QRect(1020, 200, 161, 16));
        ifjLabel_2 = new QLabel(centralWidget);
        ifjLabel_2->setObjectName(QStringLiteral("ifjLabel_2"));
        ifjLabel_2->setGeometry(QRect(1200, 140, 161, 16));
        CollectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CollectorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1394, 23));
        CollectorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CollectorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CollectorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CollectorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CollectorClass->setStatusBar(statusBar);

        retranslateUi(CollectorClass);

        QMetaObject::connectSlotsByName(CollectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CollectorClass)
    {
        CollectorClass->setWindowTitle(QApplication::translate("CollectorClass", "Collector", 0));
        imageLabel->setText(QApplication::translate("CollectorClass", "\346\232\202\346\227\240\346\225\260\346\215\256", 0));
        startButt->setText(QApplication::translate("CollectorClass", "\345\274\200\345\247\213\351\207\207\351\233\206", 0));
        endButt->setText(QApplication::translate("CollectorClass", "\347\224\237\346\210\220\345\275\223\345\211\215\346\225\260\346\215\256\345\210\260txt\346\226\207\344\273\266", 0));
        lastButt->setText(QApplication::translate("CollectorClass", "\344\270\212\344\270\200\345\270\247A", 0));
        nextButt->setText(QApplication::translate("CollectorClass", "\344\270\213\344\270\200\345\270\247D", 0));
        pathLabel->setText(QApplication::translate("CollectorClass", "<\350\267\257\345\276\204>", 0));
        fileNameLabel->setText(QApplication::translate("CollectorClass", "<\346\226\207\344\273\266\345\220\215>", 0));
        tlLabel->setText(QApplication::translate("CollectorClass", "<\345\267\246\344\270\212\350\247\222\345\235\220\346\240\207>", 0));
        brLabel->setText(QApplication::translate("CollectorClass", "<\345\217\263\344\270\213\350\247\222\345\235\220\346\240\207>", 0));
        iftLabel->setText(QApplication::translate("CollectorClass", "<\351\243\237\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        ifjLabel->setText(QApplication::translate("CollectorClass", "<\351\243\237\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        videoButt->setText(QApplication::translate("CollectorClass", "\350\247\243\346\236\220\350\247\206\351\242\221\346\265\201", 0));
        selectButt->setText(QApplication::translate("CollectorClass", "\351\207\215\345\256\232\344\275\215\350\247\206\351\242\221\346\226\207\344\273\266", 0));
        label->setText(QApplication::translate("CollectorClass", "\344\273\216", 0));
        tfjLabel->setText(QApplication::translate("CollectorClass", "<\345\260\276\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        bjLabel->setText(QApplication::translate("CollectorClass", "<\346\213\207\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        btLabel->setText(QApplication::translate("CollectorClass", "<\346\213\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        rLabel->setText(QApplication::translate("CollectorClass", "\345\217\263\346\211\213\357\274\232", 0));
        rfjLabel->setText(QApplication::translate("CollectorClass", "<\346\227\240\345\220\215\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        mftLabel->setText(QApplication::translate("CollectorClass", "<\344\270\255\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        rftLabel->setText(QApplication::translate("CollectorClass", "<\346\227\240\345\220\215\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        tftLabel_l->setText(QApplication::translate("CollectorClass", "<\345\260\276\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        mftLabel_l->setText(QApplication::translate("CollectorClass", "<\344\270\255\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        iftLabel_l->setText(QApplication::translate("CollectorClass", "<\351\243\237\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        tfjLabel_2->setText(QApplication::translate("CollectorClass", "<\345\260\276\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        mfjLabel->setText(QApplication::translate("CollectorClass", "<\344\270\255\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        bjLabel_2->setText(QApplication::translate("CollectorClass", "<\346\213\207\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        tftLabel->setText(QApplication::translate("CollectorClass", "<\345\260\276\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        rftLabel_l->setText(QApplication::translate("CollectorClass", "<\346\227\240\345\220\215\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        tlLabel_2->setText(QApplication::translate("CollectorClass", "<\345\267\246\344\270\212\350\247\222\345\235\220\346\240\207>", 0));
        bjLabel_l->setText(QApplication::translate("CollectorClass", "<\346\213\207\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        tlLabel_l->setText(QApplication::translate("CollectorClass", "<\345\267\246\344\270\212\350\247\222\345\235\220\346\240\207>", 0));
        ifjLabel_l->setText(QApplication::translate("CollectorClass", "<\351\243\237\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        tfjLabel_l->setText(QApplication::translate("CollectorClass", "<\345\260\276\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        rfjLabel_l->setText(QApplication::translate("CollectorClass", "<\346\227\240\345\220\215\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        lLabel->setText(QApplication::translate("CollectorClass", "\345\267\246\346\211\213\357\274\232", 0));
        btLabel_2->setText(QApplication::translate("CollectorClass", "<\346\213\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        iftLabel_2->setText(QApplication::translate("CollectorClass", "<\351\243\237\346\214\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        brLabel_2->setText(QApplication::translate("CollectorClass", "<\345\217\263\344\270\213\350\247\222\345\235\220\346\240\207>", 0));
        btLabel_l->setText(QApplication::translate("CollectorClass", "<\346\213\207\346\214\207\345\260\226\345\235\220\346\240\207>", 0));
        brLabel_l->setText(QApplication::translate("CollectorClass", "<\345\217\263\344\270\213\350\247\222\345\235\220\346\240\207>", 0));
        mfjLabel_l->setText(QApplication::translate("CollectorClass", "<\344\270\255\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
        ifjLabel_2->setText(QApplication::translate("CollectorClass", "<\351\243\237\346\214\207\345\205\263\350\212\202\345\235\220\346\240\207>", 0));
    } // retranslateUi

};

namespace Ui {
    class CollectorClass: public Ui_CollectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLLECTOR_H
