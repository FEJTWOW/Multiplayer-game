QT += testlib network
QT += core widgets gui
#QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_serttest.cpp


#INCLUDEPATH += ../utils/
#LIBS += -L../utils -lutils


#INCLUDEPATH += ../server2/
#LIBS += -L../server2 -lserver2


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../utils/release/ -lutils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../utils/debug/ -lutils
else:unix: LIBS += -L$$OUT_PWD/../utils/ -lutils

INCLUDEPATH += $$PWD/../utils
DEPENDPATH += $$PWD/../utils

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../server2/release/ -lserver2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../server2/debug/ -lserver2
else:unix: LIBS += -L$$OUT_PWD/../server2/ -lserver2

INCLUDEPATH += $$PWD/../server2
DEPENDPATH += $$PWD/../server2
