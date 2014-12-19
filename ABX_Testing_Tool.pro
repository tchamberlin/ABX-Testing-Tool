#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T17:57:29
#
#-------------------------------------------------

QT       += core gui multimedia testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WHY
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    playback.cpp \
    scorekeeper.cpp \
    player.cpp \
    fancyslider.cpp

HEADERS  += mainwindow.h \
    playback.h \
    scorekeeper.h \
    player.h \
    fancyslider.h

FORMS    += \
    mainwindow.ui \
    playback.ui

RESOURCES +=
