
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

