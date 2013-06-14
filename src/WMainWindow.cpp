
#include "WActionManager.h"
#include "WMainWindow.h"
#include "WCentralWidget.h"
#include "WStatusBar.h"
#include "WEditor.h"
#include "WEditorProxy.h"
#include "WFinder.h"
#include "WDockWidget.h"
#include "WDockEditorMap.h"


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
#include <QDockWidget>
#include <QCloseEvent>

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

    mFinder = Finder::instance();
    mFinder->setFindAction(mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND));
    mFinder->setReplaceAction(mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_REPLACE));
    mFinder->setFindInFilesAction(mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_IN_FILES));

    this->resize(mSettings->hidden->getMWSize());
    this->move(mSettings->hidden->getMWPosition());
    this->setWindowIcon(QIcon(":/wolverine.png"));

    createMenusAndToolbars();
    createDocks();


    setCentralWidget(mCentralWidget);
    setStatusBar(new StatusBar(this));

    Popup::initialize();

    connect( mSettings->general, SIGNAL(appCustomizeEnabledChanged(bool)),
                           this, SLOT(onAppCustimizeEnabledChanged(bool)), Qt::DirectConnection );
    this->onAppCustimizeEnabledChanged(mSettings->general->isAppCustomizeEnabled());


    //showDockWidget(new QDockWidget(tr("Explorer")), Qt::LeftDockWidgetArea, tr("Explorer"));

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




void MainWindow::addDockWidget(QDockWidget *widget)
{
    mDocks.append(widget);
    widget->hide();

    bool customizeEnabled = mSettings->general->isAppCustomizeEnabled();
    widget->setFeatures( customizeEnabled ? (widget->features() | QDockWidget::DockWidgetMovable) : (widget->features() & ~QDockWidget::DockWidgetMovable) );
    widget->setFeatures( customizeEnabled ? (widget->features() | QDockWidget::DockWidgetFloatable) : (widget->features() & ~QDockWidget::DockWidgetFloatable) );

    connect( widget, SIGNAL(topLevelChanged(bool)),
               this, SLOT(onDockTopLevelChanged(bool)) );
}


void MainWindow::addDockWidget(QDockWidget *widget, Qt::DockWidgetArea area)
{
    addDockWidget(widget);
    QMainWindow::addDockWidget(area, widget);
}


void MainWindow::addDockWidget(QDockWidget *widget, QDockWidget *tabifyTo)
{
    addDockWidget(widget);
    QMainWindow::tabifyDockWidget(tabifyTo, widget);
}





void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!mCentralWidget->closeAllTabs(true))
        event->ignore();
}


void MainWindow::createMenusAndToolbars()
{
    QtManagedToolBar *toolbar = new QtManagedToolBar(this, W_ACTION_GROUP_GENERAL);
    toolbar->setWindowTitle(tr("Main ToolBar"));

    QAction *action;
    QMenu *tmpMenu;
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
               mFinder, SLOT(showFindWidget()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_FIND, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_NEXT);
    //action->setIcon(QIcon(":/find.png"));
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(findNext()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_FIND, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_PREV);
    //action->setIcon(QIcon(":/find.png"));
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(findPrev()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_FIND, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_REPLACE);
    action->setIcon(QIcon(":/replace.png"));
    connect( action, SIGNAL(triggered()),
               mFinder, SLOT(showReplaceWidget()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_REPLACE, action);

    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_IN_FILES);
    action->setIcon(QIcon(":/find_in_files.png"));
    connect( action, SIGNAL(triggered()),
               mFinder, SLOT(showFindInFilesWidget()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_FIND_IN_FILES, action);

    menu->addSeparator();

    tmpMenu = menu->addMenu(tr("Mark All"));
    action = tmpMenu->addAction(tr("Set 1st Style"));
    action->setData(1);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(markAll()) );
    action = tmpMenu->addAction(tr("Set 2nd Style"));
    action->setData(2);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(markAll()) );
    action = tmpMenu->addAction(tr("Set 3rd Style"));
    action->setData(3);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(markAll()) );
    action = tmpMenu->addAction(tr("Set 4th Style"));
    action->setData(4);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(markAll()) );
    action = tmpMenu->addAction(tr("Set 5th Style"));
    action->setData(5);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(markAll()) );

    tmpMenu = menu->addMenu(tr("Unmark All"));
    action = tmpMenu->addAction(tr("Clear 1st Style"));
    action->setData(1);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(unmarkAll()) );
    action = tmpMenu->addAction(tr("Clear 2nd Style"));
    action->setData(2);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(unmarkAll()) );
    action = tmpMenu->addAction(tr("Clear 3rd Style"));
    action->setData(3);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(unmarkAll()) );
    action = tmpMenu->addAction(tr("Clear 4th Style"));
    action->setData(4);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(unmarkAll()) );
    action = tmpMenu->addAction(tr("Clear 5th Style"));
    action->setData(5);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(unmarkAll()) );

    tmpMenu = menu->addMenu(tr("Jump Next"));
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE1);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpNextMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE2);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpNextMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE3);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpNextMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE4);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpNextMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE5);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpNextMark()) );
    tmpMenu->addAction(action);

    tmpMenu = menu->addMenu(tr("Jump Prev"));
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE1);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpPrevMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE2);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpPrevMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE3);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpPrevMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE4);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpPrevMark()) );
    tmpMenu->addAction(action);
    action = mActionManager->getAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE5);
    connect(  action, SIGNAL(triggered()),
             mFinder, SLOT(jumpPrevMark()) );
    tmpMenu->addAction(action);


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

    tmpMenu = menu->addMenu(action->text());
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
    action->setChecked(mSettings->general->isSynchVEnabled());
    connect(             action, SIGNAL(toggled(bool)),
             mSettings->general, SLOT(setSynchVEnabled(bool)), Qt::DirectConnection );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SYNC_V, action);

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_SYNC_H);
    action->setIcon(QIcon(":/sync_h.png"));
    action->setCheckable(true);
    action->setChecked(mSettings->general->isSynchHEnabled());
    connect(             action, SIGNAL(toggled(bool)),
             mSettings->general, SLOT(setSynchHEnabled(bool)), Qt::DirectConnection );
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

    action = mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_MINI_MAP);
    action->setIcon(QIcon(":/map.png"));
    action->setCheckable(true);
    action->setChecked(false);
    // action is connected within dock widget
    menu->addAction(action);
    toolbar->addAction(W_ACTION_MINI_MAP, action, true);

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

void MainWindow::createDocks()
{
    QtDockWidget *widget;

    this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    this->setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
    this->setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);

    // Finder
    addDockWidget(mFinder->getFindReqDock(), Qt::BottomDockWidgetArea);
    addDockWidget(mFinder->getFindResDock(), mFinder->getFindReqDock());

    // MiniMap
    widget = new DockEditorMap();
    widget->addAction(mActionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_MINI_MAP));
    addDockWidget(widget, Qt::RightDockWidgetArea);

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



void MainWindow::onAppCustimizeEnabledChanged(bool enabled)
{
    foreach(QtManagedToolBar *toolbar, mToolbars) {
        toolbar->setManagerEnabled(enabled);
    }

    foreach(QDockWidget *dock, mDocks) {
        dock->setFeatures( enabled ? (dock->features() | QDockWidget::DockWidgetMovable) : (dock->features() & ~QDockWidget::DockWidgetMovable) );
        if(!dock->isFloating())
            dock->setFeatures( enabled ? (dock->features() | QDockWidget::DockWidgetFloatable) : (dock->features() & ~QDockWidget::DockWidgetFloatable) );
    }
}

void MainWindow::onDockTopLevelChanged(bool topLevel)
{
    if(!topLevel) {
        QDockWidget *dock = dynamic_cast<QDockWidget*>(sender());
        bool enabled = mSettings->general->isAppCustomizeEnabled();
        dock->setFeatures( enabled ? (dock->features() | QDockWidget::DockWidgetFloatable) : (dock->features() & ~QDockWidget::DockWidgetFloatable) );
    }
}

