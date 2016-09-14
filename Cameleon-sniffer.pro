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
    daemon/ModuleWorker.cpp \
    modules/AModule.cpp \
    modules/Dummy.cpp \
    daemon/Core.cpp \
    daemon/ModuleWorkerPool.cpp \
    modules/DnsWatcher.cpp \
    modules/ASniffer.cpp

HEADERS += \
    Debug.hh \
    network/BaseSocket.hh \
    daemon/AbstractWorker.hpp \
    daemon/WorkerFactory.hpp \
    daemon/ModuleWorker.hh \
    modules/AModule.hh \
    modules/Dummy.hh \
    daemon/Core.hh \
    daemon/ModuleWorkerPool.hh \
    modules/DnsWatcher.hh \
    modules/ModuleFactory.hpp \
    modules/ASniffer.hh

