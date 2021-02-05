QT += testlib gui widgets core

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_player_test.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../serverUtils/release/ -lserverUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../serverUtils/debug/ -lserverUtils
else:unix: LIBS += -L$$OUT_PWD/../../serverUtils/ -lserverUtils

INCLUDEPATH += $$PWD/../../serverUtils
DEPENDPATH += $$PWD/../../serverUtils

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../utils/release/ -lutils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../utils/debug/ -lutils
else:unix: LIBS += -L$$OUT_PWD/../../utils/ -lutils

INCLUDEPATH += $$PWD/../../utils
DEPENDPATH += $$PWD/../../utils
