
QT       *= core gui


#uncomment if you want to build project with libraries - see ../wolverine_build.pro
#CONFIG   += uselib

TEMPLATE  = app
TARGET    = Wolverine

include(../extlib/qtactionmanager/qtactionmanager.pri)
include(../extlib/qtconfig/qtconfig.pri)
include(../extlib/qtmanagedtoolbar/qtmanagedtoolbar.pri)
include(../extlib/qtsingleapplication/qtsingleapplication.pri)

SOURCES     += \
        ../src/main.cpp \
    ../src/settings/CfgAppSettings.cpp

HEADERS     += \
    ../src/settings/CfgAppSettings.h \
    ../src/settings/CfgGeneralSettings.h \
    ../src/settings/CfgHiddenSettings.h \
    ../src/settings/CfgScintillaSettings.h

INCLUDEPATH += \
        ../src/settings

RESOURCES   += \
        ../resources/images.qrc 

