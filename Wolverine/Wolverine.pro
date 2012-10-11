
QT       += core gui

TARGET = Wolverine
TEMPLATE = app


include(../extlib/qtmanagedtoolbar/qtmanagedtoolbar.pri)

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

RESOURCES += \
    ../resources/images.qrc 

