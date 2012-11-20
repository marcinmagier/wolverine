
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
    m_settings = AppSettings::instance();
    mActionManager = new ActionManager();
    m_settingsDialog = new DlgSettings(mActionManager, this);

    this->resize(m_settings->hidden->getMWSize());
    this->move(m_settings->hidden->getMWPosition());

    createMenusAndToolbars();

    setCentralWidget(new CentralWidget(this));
}

MainWindow::~MainWindow()
{
    m_settings->hidden->setMWPosition(this->pos());
    m_settings->hidden->setMWSize(this->size());

    delete m_settingsDialog;
    delete mActionManager;

    //These variables are deleted by Qt
    //CentralWidget
}

void MainWindow::createMenusAndToolbars()
{
    QMenu *menu;
    QAction *action;
    QtManagedToolBar *toolbar;

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
