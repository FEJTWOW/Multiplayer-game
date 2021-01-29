#-------------------------------------------------
#
# Project created by QtCreator 2021-01-18T21:15:11
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    player.cpp \
    bullet.cpp \
    enemy.cpp \
    score.cpp \
    game.cpp \
    settings.cpp \
    obstacle.cpp \
    network.cpp \
    clientsocket.cpp

HEADERS += \
    gamestate.h \
    player.h \
    bullet.h \
    enemy.h \
    score.h \
    game.h \
    settings.h \
    obstacle.h \
    network.h \
    clientsocket.h

FORMS +=

#RESOURCES += \
#    PlayersResources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../utils/release/ -lutils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../utils/debug/ -lutils
else:unix: LIBS += -L$$OUT_PWD/../utils/ -lutils

INCLUDEPATH += $$PWD/../utils
DEPENDPATH += $$PWD/../utils
