QT += core network testlib
QT -= gui

QMAKE_CXX   =   clang++
QMAKE_CC    =   clang

TARGET = cameleon-daemon

CONFIG += console
CONFIG += C++11
CONFIG -= app_bundle

LIBS += -ltins

unix:MOC_DIR = tmp/
unix:OBJECTS_DIR = tmp/

TEMPLATE = app

SOURCES += \
    main.cpp \
    network/BaseSocket.cpp \
    modules/AModule.cpp \
    daemon/Core.cpp \
    modules/DnsWatcher.cpp \
    daemon/ModuleWorker.cpp \
    daemon/ModuleWorkerPool.cpp

HEADERS += \
    Debug.hh \
    network/BaseSocket.hh \
    modules/AModule.hh \
    daemon/Core.hh \
    modules/DnsWatcher.hh \
    modules/ModuleFactory.hpp \
    daemon/AbstractWorker.hpp \
    daemon/WorkerFactory.hpp \
    daemon/ModuleWorker.hh \
    daemon/ModuleWorkerPool.hh

