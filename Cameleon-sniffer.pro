QT += core network testlib
QT -= gui

QMAKE_CXX   =   clang++
QMAKE_CC    =   clang

TARGET = cameleon

CONFIG += console
CONFIG += C++11
CONFIG -= app_bundle

LIBS += -ltins

unix:MOC_DIR = tmp/
unix:OBJECTS_DIR = tmp/

TEMPLATE = app

SOURCES += \
    main.cpp

