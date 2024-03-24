#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T10:16:14
#
#-------------------------------------------------

QT       += core gui serialport network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = laser_controller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serial.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
