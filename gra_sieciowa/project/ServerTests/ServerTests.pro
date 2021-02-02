QT += testlib
QT += core widgets gui network

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_servertests.cpp

INCLUDEPATH += ../utils
LIBS += -L../utils -lutils


INCLUDEPATH += ../server2
LIBS += -L../server2 -lserver2
