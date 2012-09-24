#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T22:36:53
#
#-------------------------------------------------

QT       += core gui

TARGET = Wolverine
TEMPLATE = app


SOURCES += \
    ../lib/Settings.cpp \
    ../src/main.cpp \
    ../src/settings/AppSettings.cpp

HEADERS  += \
    ../lib/Settings.h \
    ../src/settings/ScintillaSettings.h \
    ../src/settings/HiddenSettings.h \
    ../src/settings/GeneralSettings.h \
    ../src/settings/AppSettings.h

INCLUDEPATH += ../lib \
    ../src/settings
