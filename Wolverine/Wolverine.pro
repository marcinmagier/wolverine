
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

include(../extlib/qtscintilla/qtscintilla.pri)
#LIBS         += -lqscintilla2


SOURCES      += \
                ../src/main.cpp \
                ../src/settings/DlgSettings.cpp \
                ../src/settings/PageGeneral.cpp \
                ../src/settings/PageScintilla.cpp \
                ../src/settings/CfgAppSettings.cpp \
                ../src/settings/CfgDynamicSettings.cpp \
                ../src/settings/CfgGeneralSettings.cpp \
                ../src/settings/CfgHiddenSettings.cpp \
                ../src/settings/CfgScintillaSettings.cpp \
                ../src/settings/CfgStartupSettings.cpp \
                ../src/WActionManager.cpp \
                ../src/WCentralWidget.cpp \
                ../src/WDocument.cpp \
                ../src/WLib.cpp \
                ../src/WMainWindow.cpp \
                ../src/WStatusBar.cpp \
    ../src/qtpopup.cpp

HEADERS      += \
                ../src/wolverine_cfg.h \
                ../src/WStatusBar.h \
                ../src/settings/DlgSettings.h \
                ../src/settings/PageGeneral.h \
                ../src/settings/PageScintilla.h \
                ../include/CfgAppSettings.h \
                ../include/CfgDynamicSettings.h \
                ../include/CfgGeneralSettings.h \
                ../include/CfgHiddenSettings.h \
                ../include/CfgScintillaSettings.h \
                ../include/CfgStartupSettings.h \
                ../include/WActionManager.h \
                ../include/WCentralWidget.h \
                ../include/WDocument.h \
                ../include/WLib.h \
                ../include/WMainWindow.h \
    ../src/qtpopup.h

INCLUDEPATH  += \
                ../include \
                ../src \
                ../src/settings

RESOURCES    += \
                ../resources/images.qrc 

FORMS        += \
                ../src/settings/PageGeneral.ui \
                ../src/settings/PageScintilla.ui

TRANSLATIONS += \
                ../translations/wolverine_en_US.ts \
                ../translations/wolverine_pl_PL.ts
