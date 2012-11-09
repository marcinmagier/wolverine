
#include "WMainWindow.h"
#include "WCentralWidget.h"

#include "qtactionmanager.h"
#include "qtmanagedtoolbar.h"
#include "CfgAppSettings.h"
#include "DlgSettings.h"


#include <QMenu>
#include <QMenuBar>



using namespace Wolverine;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_settings = AppSettings::instance();
    m_settingsDialog = new DlgSettings(m_settings, this);

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

    //These variables are deleted by Qt
    //CentralWidget
}

void MainWindow::createMenusAndToolbars()
{
    QMenu *menu;
    QAction *action;
    QtManagedToolBar *toolbar;
    QtActionManager *actionManager = QtActionManager::instance();


    menu = menuBar()->addMenu(tr("&File"));
    toolbar = new QtManagedToolBar(this, "File");

    action = new QAction(QIcon(":/new.png"), tr("&New"), this);
    action->setShortcut(tr("Ctrl+N"));
    action->setStatusTip(tr("Create a new file"));
    //connect
    menu->addAction(action);
    toolbar->addAction(action);
    actionManager->addAction("File", action);

    action = new QAction(QIcon(":/open.png"), tr("&Open..."), this);
    action->setShortcut(tr("Ctrl+O"));
    //connect
    menu->addAction(action);
    toolbar->addAction(action);
    actionManager->addAction("File", action);

    action = new QAction(QIcon(":/save.png"), tr("&Save"), this);
    action->setShortcut(tr("Ctrl+S"));
    action->setStatusTip(tr("Save"));
    //connect
    menu->addAction(action);
    toolbar->addAction(action);
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
    toolbar->addAction(action);
    actionManager->addAction("File", action);

    m_menus["File"] = menu;
    m_toolbars["File"] = toolbar;
    addToolBar(toolbar);
    toolbar->setIconSize(QSize(16,16));
    toolbar->restoreConfig();



    menu = menuBar()->addMenu(tr("&Edit"));
    toolbar = new QtManagedToolBar(this, "Edit");

    action = new QAction(QIcon(":/cut.png"), tr("Cut"), this);
    action->setShortcut(tr("Ctrl+X"));
    //connect
    menu->addAction(action);
    toolbar->addAction(action);
    actionManager->addAction("Edit", action);

    action = new QAction(QIcon(":/copy.png"), tr("&Copy"), this);
    action->setShortcut(tr("Ctrl+C"));
    //connect
    menu->addAction(action);
    toolbar->addAction(action);
    actionManager->addAction("Edit", action);

    action = new QAction(QIcon(":/paste.png"), tr("&Paste"), this);
    action->setShortcut(tr("Ctrl+V"));
    //connect
    menu->addAction(action);
    toolbar->addAction(action);
    actionManager->addAction("Edit", action);

    m_menus["Edit"] = menu;
    m_toolbars["Edit"] = toolbar;
    addToolBar(toolbar);
    toolbar->setIconSize(QSize(16,16));
    toolbar->restoreConfig();

}
