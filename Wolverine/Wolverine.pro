
QT       *= core gui widgets


# uncomment if you want to build project with libraries - see ../wolverine_build.pro
#CONFIG   += uselib

TEMPLATE  = app
TARGET    = Wolverine


include(../extlib/qtlogger/qtlogger.pri)
include(../extlib/qtmisclib/qtmisclib.pri)
include(../extlib/qtsingleapplication/qtsingleapplication.pri)
include(../extlib/qtwidgets/qtwidgets.pri)

include(../extlib/qtscintilla/qtscintilla.pri)
#LIBS         += -lqscintilla2


SOURCES      += \
                ../src/main.cpp \
                ../src/editor/WEditor.cpp \
                ../src/editor/WEditor_slots.cpp \
                ../src/editor/WEditorBinder.cpp \
                ../src/editor/WEditorLexerCfg.cpp \
                ../src/editor/WEditorLexerManager.cpp \
                ../src/editor/WEditorLexerManagerWidget.cpp \
                ../src/editor/WEditorProxy.cpp \
                ../src/editor/WEditorProxy_slots.cpp \
                ../src/editor/qtscintilla.cpp \
                ../src/settings/DlgSettings.cpp \
                ../src/settings/PageGeneral.cpp \
                ../src/settings/PageView.cpp \
                ../src/settings/PageEditor.cpp \
                ../src/settings/PageEditorCodec.cpp \
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
                ../src/WLib.cpp \
                ../src/WMainWindow.cpp \
                ../src/WPanel.cpp \
                ../src/WPanelTabBar.cpp \
                ../src/WPanelTabContent.cpp \
                ../src/WPopup.cpp \
                ../src/WStatusBar.cpp


HEADERS      += \
                ../src/wolverine_cfg.h \
                ../src/WPanel.h \
                ../src/WPanelTabBar.h \
                ../src/WPanelTabContent.h \
                ../src/WPopup.h \
                ../src/WStatusBar.h \
                ../src/editor/WEditorLexerManagerWidget.h \
                ../src/settings/DlgSettings.h \
                ../src/settings/PageGeneral.h \
                ../src/settings/PageView.h \
                ../src/settings/PageEditor.h \
                ../src/settings/PageEditorCodec.h \
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
                ../include/WEditorLexerCfg.h \
                ../include/WEditorLexerManager.h \
                ../include/WEditorProxy.h \
                ../include/WLib.h \
                ../include/WMainWindow.h \
                ../include/qtscintilla.h


INCLUDEPATH  += \
                ../include \
                ../src \
                ../src/settings


RESOURCES    += \
                ../resources/images.qrc


RC_FILE      += \
                ../resources/appicon/wolverine.rc


FORMS        += \
                ../src/editor/WEditorLexerManagerWidget.ui \
                ../src/settings/PageGeneral.ui \
                ../src/settings/PageView.ui \
                ../src/settings/PageEditor.ui \
                ../src/settings/PageEditorCodec.ui


TRANSLATIONS += \
                ../translations/wolverine_en_US.ts \
                ../translations/wolverine_pl_PL.ts
