#-------------------------------------------------
#
# Project created by QtCreator 2012-09-24T22:36:53
#
#-------------------------------------------------

QT       += core gui

TARGET = Wolverine
TEMPLATE = app


SOURCES += \
    ../src/main.cpp \
    ../src/settings/AppConfig.cpp \
    ../extlib/qtconfig/qtconfig.cpp

HEADERS  += \
    ../src/settings/ScintillaSettings.h \
    ../src/settings/HiddenSettings.h \
    ../src/settings/GeneralSettings.h \
    ../src/settings/AppConfig.h \
    ../extlib/qtconfig/qtconfig.h

INCLUDEPATH += ../extlib/qtconfig \
    ../src/settings
