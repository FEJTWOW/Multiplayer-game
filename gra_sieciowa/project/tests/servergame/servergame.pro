QT += testlib
QT -= gui
QT += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_servergame_test.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../utils/release/ -lutils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../utils/debug/ -lutils
else:unix: LIBS += -L$$OUT_PWD/../../utils/ -lutils

INCLUDEPATH += $$PWD/../../utils
DEPENDPATH += $$PWD/../../utils

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../clientUtils/release/ -lclientUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../clientUtils/debug/ -lclientUtils
else:unix: LIBS += -L$$OUT_PWD/../../clientUtils/ -lclientUtils

INCLUDEPATH += $$PWD/../../clientUtils
DEPENDPATH += $$PWD/../../clientUtils

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../serverUtils/release/ -lserverUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../serverUtils/debug/ -lserverUtils
else:unix: LIBS += -L$$OUT_PWD/../../serverUtils/ -lserverUtils

INCLUDEPATH += $$PWD/../../serverUtils
DEPENDPATH += $$PWD/../../serverUtils
