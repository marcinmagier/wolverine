
QT       *= core gui


# uncomment if you want to build project with libraries - see ../wolverine_build.pro
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
    ../src/settings/CfgAppSettings.cpp \
    ../src/MainWindow.cpp \
    ../src/settings/DlgSettings.cpp \
    ../src/settings/PageGeneral.cpp \
    ../src/settings/PageScintilla.cpp

HEADERS     += \
    ../include/CfgAppSettings.h \
    ../include/CfgGeneralSettings.h \
    ../include/CfgHiddenSettings.h \
    ../include/CfgScintillaSettings.h \
    ../src/MainWindow.h \
    ../src/settings/DlgSettings.h \
    ../src/settings/PageGeneral.h \
    ../src/settings/PageScintilla.h

INCLUDEPATH += \
        ../include \
        ../src/settings

RESOURCES   += \
        ../resources/images.qrc 

FORMS += \
    ../src/settings/PageGeneral.ui \
    ../src/settings/PageScintilla.ui

