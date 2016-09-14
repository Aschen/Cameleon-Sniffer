QT += core network
QT -= gui

QMAKE_CXX   =   clang++
QMAKE_CC    =   clang

TARGET = cameleon-client

CONFIG += console
CONFIG += C++11
CONFIG -= app_bundle

unix:MOC_DIR = tmp/
unix:OBJECTS_DIR = tmp/

TEMPLATE = app

SOURCES += \
    main.cpp \
    ../network/BaseSocket.cpp \
    Sender.cpp

HEADERS += \
    ../network/BaseSocket.hh \
    Sender.hh \
    Debug.hh \
    Debug.hh

