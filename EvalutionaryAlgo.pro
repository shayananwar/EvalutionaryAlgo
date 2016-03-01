#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T23:07:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = EvalutionaryAlgo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphs.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    graphs.h \
    qcustomplot.h \
    config.h

FORMS    += mainwindow.ui \
    graphs.ui
