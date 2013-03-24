
#include "WActionManager.h"
#include "WMainWindow.h"
#include "WCentralWidget.h"
#include "WStatusBar.h"
#include "WEditor.h"
#include "WEditorProxy.h"

#include "qtmanagedtoolbar.h"
#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
#include "CfgScintillaSettings.h"
#include "DlgSettings.h"

#include "Logger.h"

#include <QMenu>
#include <QMenuBar>
#include <QStringList>

#include "WPopup.h"



using namespace Wolverine;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mSettings = AppSettings::instance();
    mActionManager = ActionManager::instance();
    mSettingsDialog = new DlgSettings(this);

    mCentralWidget = new CentralWidget(this);
    mEditorProxy = EditorProxy::instance();
    connect(mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                    this, SLOT(onCurrentEditorChanged(Editor*)) );

    this->resize(mSettings->hidden->getMWSize());
    this->move(mSettings->hidden->getMWPosition());
    this->setWindowIcon(QIcon(":/wolverine.png"));

    createMenusAndToolbars();


    setCentralWidget(mCentralWidget);
    setStatusBar(new StatusBar(this));

    Popup::initialize();

}

MainWindow::~MainWindow()
{
    mSettings->hidden->setMWPosition(this->pos());
    mSettings->hidden->setMWSize(this->size());

    delete mSettingsDialog;
    //These variables are deleted by Qt
    //CentralWidget
    //AppSettings
    //ActionManager
}

void MainWindow::closeEvent(QCloseEvent *)
{
    mCentralWidget->closeAllTabs(true);
}


void MainWindow::createMenusAndToolbars()
{
    QtManagedToolBar *toolbar = new QtManagedToolBar(this, W_ACTION_GROUP_GENERAL);
    toolbar->setManagerEnabled(mSettings->general->isAppCustomizeEnabled());
    connect( mSettings->general, SIGNAL(appCustomizeEnabledChanged(bool)),
                        toolbar, SLOT(setManagerEnabled(bool)), Qt::DirectConnection );

    QAction *action;
    QMenu *menu = menuBar()->addMenu(tr("File"));

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_NEW);
    action->setIcon(QIcon(":/new.png"));
    connect(        action, SIGNAL(triggered()),
            mCentralWidget, SLOT(newTab()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_NEW, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_OPEN);
    action->setIcon(QIcon(":/open.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(openTabForm()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_OPEN, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_RELOAD);
    action->setIcon(QIcon(":/refresh.png"));
    connect(       action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onReload()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_RELOAD, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE);
    action->setIcon(QIcon(":/save_blue.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(saveTab()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SAVE, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE_AS);
    //action->setIcon(QIcon(":/save_blue.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(saveTabForm()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_SAVE_AS, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE_ALL);
    action->setIcon(QIcon(":/save_all.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(saveAllTabs()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SAVE_ALL, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE);
    action->setIcon(QIcon(":/close.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(closeTab()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_CLOSE, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_OTHERS);
    //action->setIcon(QIcon(":/close.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(closeOtherTabs()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_CLOSE_OTHERS, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_ALL);
    action->setIcon(QIcon(":/close_all.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(closeAllTabs()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_CLOSE_ALL, action);

    menu->addSeparator();

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_EXIT);
    //action->setIcon(QIcon(":/close_all.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(close()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_EXIT, action);

    mMenus[W_ACTION_GROUP_FILE] = menu;
    toolbar->addSeparator();



    menu = menuBar()->addMenu(tr("Edit"));

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_UNDO);
    action->setIcon(QIcon(":/undo.png"));
    connect(    action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onUndo()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_UNDO, action);

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_REDO);
    action->setIcon(QIcon(":/redo.png"));
    connect(    action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onRedo()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_REDO, action);

    menu->addSeparator();

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_CUT);
    action->setIcon(QIcon(":/cut.png"));
    connect(    action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onCut()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_CUT, action);

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_COPY);
    action->setIcon(QIcon(":/copy.png"));
    connect(    action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onCopy()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_COPY, action);

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_PASTE);
    action->setIcon(QIcon(":/paste.png"));
    connect(    action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onPaste()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_PASTE, action);

    mMenus[W_ACTION_GROUP_EDIT] = menu;
    toolbar->addSeparator();


    menu = menuBar()->addMenu(tr("Search"));

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND);
    action->setIcon(QIcon(":/find.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onFindTriggered()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_FIND, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_NEXT);
    //action->setIcon(QIcon(":/find.png"));
    //connect( action, SIGNAL(triggered()),
    //           this, SLOT(onFindTriggered()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_FIND, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_PREV);
    //action->setIcon(QIcon(":/find.png"));
    //connect( action, SIGNAL(triggered()),
    //           this, SLOT(onFindTriggered()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_FIND, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_IN_FILES);
    action->setIcon(QIcon(":/find_in_files.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onFindInFilesTriggered()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_FIND_IN_FILES, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_REPLACE);
    action->setIcon(QIcon(":/replace.png"));
    connect( action, SIGNAL(triggered()),
               this, SLOT(onReplaceTriggered()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_REPLACE, action);

    mMenus[W_ACTION_GROUP_SEARCH] = menu;
    toolbar->addSeparator();


    menu = menuBar()->addMenu(tr("View"));

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_WRAP);
    action->setIcon(QIcon(":/wrap.png"));
    action->setCheckable(true);
    action->setChecked(mSettings->scintilla->isWrapModeEnabled());
    connect(               action, SIGNAL(toggled(bool)),
             mSettings->scintilla, SLOT(setWrapModeEnabled(bool)), Qt::DirectConnection );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_WRAP, action);

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_WCHARS);
    action->setIcon(QIcon(":/pilcrow.png"));
    action->setCheckable(true);
    action->setChecked(mSettings->scintilla->isShowWhiteCharsEnabled());
    connect(               action, SIGNAL(toggled(bool)),
             mSettings->scintilla, SLOT(setShowWhiteCharsEnabled(bool)), Qt::DirectConnection );
    connect(mSettings->scintilla, SIGNAL(showWhiteCharsEnabledChanged(bool)),
                          action, SLOT(setChecked(bool)), Qt::DirectConnection );
    toolbar->addAction(W_ACTION_WCHARS, action);

    QMenu *tmpMenu = menu->addMenu(action->text());
    tmpMenu->setIcon(QIcon(":/pilcrow.png"));
    action = tmpMenu->addAction(tr("Show spaces and tabs"));
    action->setCheckable(true);
    action->setChecked(mSettings->scintilla->isWhiteSpaceVisible());
    connect(               action, SIGNAL(toggled(bool)),
             mSettings->scintilla, SLOT(setWhiteSpaceVisible(bool)), Qt::DirectConnection );
    connect(mSettings->scintilla, SIGNAL(whiteSpaceVisibleChanged(bool)),
                          action, SLOT(setChecked(bool)), Qt::DirectConnection );
    action = tmpMenu->addAction(tr("Show end of lines"));
    action->setCheckable(true);
    action->setChecked(mSettings->scintilla->isEolVisible());
    connect(               action, SIGNAL(toggled(bool)),
             mSettings->scintilla, SLOT(setEolVisible(bool)), Qt::DirectConnection );
    connect(mSettings->scintilla, SIGNAL(eolVisibleChanged(bool)),
                          action, SLOT(setChecked(bool)), Qt::DirectConnection );

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_INDENT_GUIDE);
    action->setIcon(QIcon(":/indent_guide.png"));
    action->setCheckable(true);
    action->setChecked(mSettings->scintilla->isIndentGuideEnabled());
    connect(               action, SIGNAL(toggled(bool)),
             mSettings->scintilla, SLOT(setIndentGuideEnabled(bool)), Qt::DirectConnection );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_INDENT_GUIDE, action);

    tmpMenu = menu->addMenu(tr("Zoom"));
    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_ZOOM_IN);
    action->setIcon(QIcon(":/zoom_in.png"));
    connect(       action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onZoomIn()) );
    tmpMenu->addAction(action);
    toolbar->addAction(W_ACTION_ZOOM_IN, action);

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_ZOOM_OUT);
    action->setIcon(QIcon(":/zoom_out.png"));
    connect(       action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onZoomOut()) );
    tmpMenu->addAction(action);
    toolbar->addAction(W_ACTION_ZOOM_OUT, action);

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_ZOOM_DEF);
    action->setIcon(QIcon(":/zoom.png"));
    connect(       action, SIGNAL(triggered()),
             mEditorProxy, SLOT(onZoomDefault()) );
    tmpMenu->addAction(action);
    toolbar->addAction(W_ACTION_ZOOM_DEF, action);

    menu->addSeparator();

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_SYNC_V);
    action->setIcon(QIcon(":/sync_v.png"));
    action->setCheckable(true);
    //action->setChecked(mSettings->scintilla->isWrapModeEnabled());
    //connect(               action, SIGNAL(toggled(bool)),
    //         mSettings->scintilla, SLOT(setWrapModeEnabled(bool)), Qt::DirectConnection );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SYNC_V, action);

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_SYNC_H);
    action->setIcon(QIcon(":/sync_h.png"));
    action->setCheckable(true);
    //action->setChecked(mSettings->scintilla->isWrapModeEnabled());
    //connect(               action, SIGNAL(toggled(bool)),
    //         mSettings->scintilla, SLOT(setWrapModeEnabled(bool)), Qt::DirectConnection );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SYNC_H, action);

    menu->addSeparator();

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_MONITOR_MODE);
    action->setIcon(QIcon(":/monitor.png"));
    action->setCheckable(true);
    action->setChecked(false);
    // action is connected when current editor changed
    menu->addAction(action);
    toolbar->addAction(W_ACTION_MONITOR_MODE, action, true);

    mMenus[W_ACTION_GROUP_VIEW] = menu;
    toolbar->addSeparator();



    menu = menuBar()->addMenu(tr("Tools"));

    action = mActionManager->getAction(W_ACTION_GROUP_TOOLS, W_ACTION_CUSTOMIZE);
    //action->setIcon(QIcon(":/settings.png"));
    action->setChecked(mSettings->general->isAppCustomizeEnabled());
    connect(             action, SIGNAL(triggered(bool)),
             mSettings->general, SLOT(setAppCustomizeEnabled(bool)), Qt::DirectConnection );
    menu->addAction(action);

    action = mActionManager->getAction(W_ACTION_GROUP_TOOLS, W_ACTION_SETTINGS);
    action->setIcon(QIcon(":/settings.png"));
    connect(          action, SIGNAL(triggered()),
             mSettingsDialog, SLOT(showDialog()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SETTINGS, action);


    mMenus[W_ACTION_GROUP_EDIT] = menu;

    mToolbars[W_ACTION_GROUP_GENERAL] = toolbar;

    addToolBar(toolbar);
    toolbar->setIconSize(QSize(16,16));
    toolbar->restoreConfig();

}



void MainWindow::openNewFile()
{
    mCentralWidget->newTab();
}


void MainWindow::openFile(const QString &file)
{
    if(!file.isEmpty())
        mCentralWidget->openTab(file);
}


void MainWindow::onCurrentEditorChanged(Editor *editor)
{
    EditorBinder *binder = editor->getBinder();
    QAction *action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_MONITOR_MODE);
    disconnect(action, SIGNAL(toggled(bool)), 0, 0);
    action->setChecked(binder->isMonitorModeEnabled());
    connect( action, SIGNAL(toggled(bool)),
             binder, SLOT(enableMonitorMode(bool)) );

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_RELOAD);
    action->setEnabled(binder->exists());
}

void MainWindow::onFindTriggered()
{

}

void MainWindow::onFindInFilesTriggered()
{

}

void MainWindow::onReplaceTriggered()
{

}
