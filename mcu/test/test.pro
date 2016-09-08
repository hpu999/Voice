#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T14:21:21
#
#-------------------------------------------------

QT      += core gui

equals(QT_MAJOR_VERSION, 5) {
    QT      += serialport
}

equals(QT_MAJOR_VERSION, 4) {
    CONFIG  += serialport
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../mcu_imx.cpp \
    ../mcu_omap.cpp

HEADERS  += mainwindow.h \
    ../mcu.h \
    ../mcu_imx.h \
    ../mcu_omap.h

FORMS    += mainwindow.ui
