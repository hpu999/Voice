#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T08:56:44
#
#-------------------------------------------------

DEVICE = PHASCAN_II

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += $$DEVICE

TARGET = test_fpga
TEMPLATE = app

target.path = /home/root

INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp \
    ../gpio.cpp \
    ../spi.cpp \
    ../fpga.cpp \
    ../fpga_spi.cpp \
    ../group.cpp \
    ../beam.cpp \
    ../tcg.cpp

HEADERS  += mainwindow.h \
    ../beam.h \
    ../fpga.h \
    ../gpio.h \
    ../group.h \
    ../spi.h \
    ../fpga_spi.h \
    ../tcg.h

FORMS    += mainwindow.ui
