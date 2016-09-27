#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T22:18:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EgoAirWriting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    argmanager.cpp \
    imageprocessor.cpp \
    statuscontroll.cpp \
    writing.cpp \
    coordtool.cpp

HEADERS  += mainwindow.h \
    argmanager.h \
    common.h \
    imageprocessor.h \
    statuscontroll.h \
    writing.h \
    coordtool.h \
    functions.h

FORMS    += mainwindow.ui

#paths that need to be modify if needed
USER_HOME=/home/charlie
PROJECT_HOME=$${USER_HOME}/EgoFinger.HCII.SCUT/Application

# adding dynamic links of CAFFE and its dependencies
#CAFFE_ROOT=${PWD}
CAFFE_ROOT=$${PROJECT_HOME}/caffe-msra-demo


# caffe
INCLUDEPATH += $${CAFFE_ROOT}/include  $${CAFFE_ROOT}/build/src
LIBS += -L$${CAFFE_ROOT}/build/lib
LIBS += -lcaffe

# cuda
INCLUDEPATH += /usr/local/cuda/include
LIBS += -L/usr/local/cuda/lib64
LIBS += -lcudart -lcublas -lcurand

# opencv
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui

# other dependencies
LIBS += -lglog -lgflags -lprotobuf -lboost_system -lboost_thread -llmdb -lleveldb -lstdc++  -lcblas -latlas #-lcudnn

# GPen recognizer
INCLUDEPATH += $${CAFFE_ROOT}/libGPen
LIBS += -L$${CAFFE_ROOT}/libGPen
LIBS += -lGPen
