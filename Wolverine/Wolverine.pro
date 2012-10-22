
QT       *= core gui


#uncomment if you want to build project with libraries - see ../wolverine_build.pro
#CONFIG   += uselib

TEMPLATE  = app
TARGET    = Wolverine

include(../extlib/qtactionmanager/qtactionmanager.pri)
include(../extlib/qtconfig/qtconfig.pri)
include(../extlib/qtlogger/qtlogger.pri)
include(../extlib/qtmanagedtoolbar/qtmanagedtoolbar.pri)
include(../extlib/qtsingleapplication/qtsingleapplication.pri)

SOURCES     += \
        ../src/main.cpp \
    ../src/CfgAppSettings.cpp

HEADERS     += \
    ../include/CfgAppSettings.h \
    ../include/CfgGeneralSettings.h \
    ../include/CfgHiddenSettings.h \
    ../include/CfgScintillaSettings.h

INCLUDEPATH += \
        ../include

RESOURCES   += \
        ../resources/images.qrc 

