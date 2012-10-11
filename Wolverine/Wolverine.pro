
QT       += core gui

TEMPLATE  = app
#CONFIG   += uselib


TARGET    = Wolverine


include(../extlib/qtconfig/qtconfig.pri)
include(../extlib/qtmanagedtoolbar/qtmanagedtoolbar.pri)
include(../extlib/qtsingleapplication/qtsingleapplication.pri)

SOURCES     += \
        ../src/main.cpp \
        ../src/settings/AppConfig.cpp 

HEADERS     += \
        ../src/settings/ScintillaSettings.h \
        ../src/settings/HiddenSettings.h \
        ../src/settings/GeneralSettings.h \
        ../src/settings/AppConfig.h 

INCLUDEPATH += \
        ../src/settings

RESOURCES   += \
        ../resources/images.qrc 

