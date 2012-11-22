
#include "WActionManager.h"
#include "WMainWindow.h"
#include "WCentralWidget.h"

#include "qtmanagedtoolbar.h"
#include "CfgAppSettings.h"
#include "CfgHiddenSettings.h"
#include "DlgSettings.h"


#include <QMenu>
#include <QMenuBar>



using namespace Wolverine;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mSettings = AppSettings::instance();
    mActionManager = ActionManager::instance();
    mSettingsDialog = new DlgSettings(this);

    this->resize(mSettings->hidden->getMWSize());
    this->move(mSettings->hidden->getMWPosition());

    createMenusAndToolbars();

    setCentralWidget(new CentralWidget(this));
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

void MainWindow::createMenusAndToolbars()
{
    QMenu *menu;
    QAction *action;
    QtManagedToolBar *toolbar = new QtManagedToolBar(this, W_ACTION_GROUP_GENERAL);


    menu = menuBar()->addMenu(tr("File"));

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_NEW);
    //connect
    menu->addAction(action);
    toolbar->addAction(W_ACTION_NEW, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_OPEN);
    //connect
    menu->addAction(action);
    toolbar->addAction(W_ACTION_OPEN, action);


    mMenus[W_ACTION_GROUP_FILE] = menu;
    menu = menuBar()->addMenu(tr("Edit"));

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_UNDO);
    //connect
    menu->addAction(action);
    toolbar->addAction(W_ACTION_UNDO, action);


    mMenus[W_ACTION_GROUP_EDIT] = menu;
    menu = menuBar()->addMenu(tr("Tools"));

    action = mActionManager->getAction(W_ACTION_GROUP_TOOLS, W_ACTION_SETTINGS);
    connect(action, SIGNAL(triggered()), mSettingsDialog, SLOT(showDialog()));
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SETTINGS, action);


    mMenus[W_ACTION_GROUP_EDIT] = menu;

    mToolbars[W_ACTION_GROUP_GENERAL] = toolbar;

    addToolBar(toolbar);
    toolbar->setIconSize(QSize(16,16));
    toolbar->restoreConfig();
/*
    menu = menuBar()->addMenu(tr("File"));
    toolbar = new QtManagedToolBar(this, "File");

    action = new QAction(QIcon(":/new.png"), tr("New"), this);
    action->setShortcut(tr("Ctrl+N"));
    action->setStatusTip(tr("Create a new file"));
    //connect
    menu->addAction(action);
    toolbar->addAction("New", action);
    mActionManager->addAction(W_ACTION_GROUP_FILE, action);

   action = new QAction(QIcon(":/open.png"), tr("Open..."), this);
    action->setShortcut(tr("Ctrl+O"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Open", action);
    actionManager->addAction("File", action);

    action = new QAction(QIcon(":/save.png"), tr("Save"), this);
    action->setShortcut(tr("Ctrl+S"));
    action->setStatusTip(tr("Save"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Save", action);
    actionManager->addAction("File", action);

    action = new QAction(tr("Save As..."), this);
    action->setShortcut(tr("Ctrl+Alt+S"));
    action->setStatusTip(tr("Save As..."));
    //connect
    menu->addAction(action);
    actionManager->addAction("File", action);

    action = new QAction(QIcon(":/save_all.png"), tr("Save All"), this);
    action->setShortcut(tr("Ctrl+Shift+S"));
    action->setStatusTip(tr("Save All"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Save All", action);
    actionManager->addAction("File", action);

    m_menus["File"] = menu;



    menu = menuBar()->addMenu(tr("&Edit"));

    action = new QAction(QIcon(":/undo.png"), tr("Undo"), this);
    action->setShortcut(tr("Ctrl+Z"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Undo", action);
    mActionManager->addAction("Edit", action);

    action = new QAction(QIcon(":/redo.png"), tr("Redo"), this);
    action->setShortcut(tr("Ctrl+Y"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Redo", action);
    actionManager->addAction("Edit", action);

    menu->addSeparator();

    action = new QAction(QIcon(":/cut.png"), tr("Cut"), this);
    action->setShortcut(tr("Ctrl+X"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Cut", action);
    actionManager->addAction("Edit", action);

    action = new QAction(QIcon(":/copy.png"), tr("Copy"), this);
    action->setShortcut(tr("Ctrl+C"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Copy", action);
    actionManager->addAction("Edit", action);

    action = new QAction(QIcon(":/paste.png"), tr("Paste"), this);
    action->setShortcut(tr("Ctrl+V"));
    //connect
    menu->addAction(action);
    toolbar->addAction("Paste", action);
    actionManager->addAction("Edit", action);

    m_menus["Edit"] = menu;



    menu = menuBar()->addMenu(tr("Tools"));

    action = new QAction(QIcon(":/settings.png"), tr("Settings"), this);
    connect(action, SIGNAL(triggered()), m_settingsDialog, SLOT(showDialog()));
    menu->addAction(action);
    toolbar->addAction("Settings", action);
    mActionManager->addAction("Settings", action);

    m_menus["Tools"] = menu;



    m_toolbars["General"] = toolbar;

    addToolBar(toolbar);
    toolbar->setIconSize(QSize(16,16));
    toolbar->restoreConfig();
*/
}
