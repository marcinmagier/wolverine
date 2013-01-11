
QT       *= core gui


# uncomment if you want to build project with libraries - see ../wolverine_build.pro
#CONFIG   += uselib

TEMPLATE  = app
TARGET    = Wolverine


include(../extlib/qtactionmanager/qtactionmanager.pri)
include(../extlib/qtconfig/qtconfig.pri)
include(../extlib/qtlogger/qtlogger.pri)
include(../extlib/qtsingleapplication/qtsingleapplication.pri)
include(../extlib/qtwidgets/qtwidgets.pri)

include(../extlib/qtscintilla/qtscintilla.pri)
#LIBS         += -lqscintilla2


SOURCES      += \
                ../src/main.cpp \
                ../src/settings/DlgSettings.cpp \
                ../src/settings/PageGeneral.cpp \
                ../src/settings/PageScintilla.cpp \
                ../src/settings/PageView.cpp \
                ../src/settings/CfgAppSettings.cpp \
                ../src/settings/CfgDynamicSettings.cpp \
                ../src/settings/CfgGeneralSettings.cpp \
                ../src/settings/CfgHiddenSettings.cpp \
                ../src/settings/CfgScintillaSettings.cpp \
                ../src/settings/CfgStartupSettings.cpp \
                ../src/settings/CfgViewSettings.cpp \
                ../src/WActionManager.cpp \
                ../src/WCentralWidget.cpp \
                ../src/WCentralWidget_slots.cpp \
                ../src/WEditor.cpp \
                ../src/WEditorBinder.cpp \
                ../src/WEditorProxy.cpp \
                ../src/WLib.cpp \
                ../src/WMainWindow.cpp \
                ../src/WPanel.cpp \
                ../src/WPanelTabBar.cpp \
                ../src/WPopup.cpp \
                ../src/WStatusBar.cpp


HEADERS      += \
                ../src/wolverine_cfg.h \
                ../src/WPanel.h \
                ../src/WPanelTabBar.h \
                ../src/WPopup.h \
                ../src/WStatusBar.h \
                ../src/settings/DlgSettings.h \
                ../src/settings/PageGeneral.h \
                ../src/settings/PageScintilla.h \
                ../src/settings/PageView.h \
                ../include/CfgAppSettings.h \
                ../include/CfgDynamicSettings.h \
                ../include/CfgGeneralSettings.h \
                ../include/CfgHiddenSettings.h \
                ../include/CfgScintillaSettings.h \
                ../include/CfgStartupSettings.h \
                ../include/CfgViewSettings.h \
                ../include/WActionManager.h \
                ../include/WCentralWidget.h \
                ../include/WEditor.h \
                ../include/WEditorBinder.h \
                ../include/WEditorProxy.h \
                ../include/WLib.h \
                ../include/WMainWindow.h


INCLUDEPATH  += \
                ../include \
                ../src \
                ../src/settings

RESOURCES    += \
                ../resources/images.qrc 

FORMS        += \
                ../src/settings/PageGeneral.ui \
                ../src/settings/PageScintilla.ui \
                ../src/settings/PageView.ui

TRANSLATIONS += \
                ../translations/wolverine_en_US.ts \
                ../translations/wolverine_pl_PL.ts
