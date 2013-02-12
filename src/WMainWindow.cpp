
#include "WActionManager.h"
#include "WMainWindow.h"
#include "WCentralWidget.h"
#include "WStatusBar.h"
#include "WEditorProxy.h"

#include "qtmanagedtoolbar.h"
#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
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

    this->resize(mSettings->hidden->getMWSize());
    this->move(mSettings->hidden->getMWPosition());

    createMenusAndToolbars();


    setCentralWidget(mCentralWidget);
    setStatusBar(new StatusBar(mCentralWidget->getCurrentEditor(), this));

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

void MainWindow::createMenusAndToolbars()
{
    QtManagedToolBar *toolbar = new QtManagedToolBar(this, W_ACTION_GROUP_GENERAL);
    toolbar->setManagerEnabled(mSettings->general->isAppCustomizeEnabled());
    connect( mSettings->general, SIGNAL(appCustomizeEnabledChanged(bool)),
                        toolbar, SLOT(setManagerEnabled(bool)), Qt::DirectConnection );

    EditorProxy *editProxy = mCentralWidget->getCurrentEditor();

    QAction *action;
    QMenu *menu = menuBar()->addMenu(tr("File"));

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_NEW);
    action->setIcon(QIcon(":/new.png"));
    connect(        action, SIGNAL(triggered()),
            mCentralWidget, SLOT(onNew()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_NEW, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_OPEN);
    action->setIcon(QIcon(":/open.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(onOpenForm()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_OPEN, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE);
    action->setIcon(QIcon(":/save_blue.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(onSave()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SAVE, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE_AS);
    //action->setIcon(QIcon(":/save_blue.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(onSaveForm()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_SAVE_AS, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE_ALL);
    action->setIcon(QIcon(":/save_all.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(onSaveAll()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_SAVE_ALL, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE);
    action->setIcon(QIcon(":/close.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(onClose()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_CLOSE, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_OTHERS);
    //action->setIcon(QIcon(":/close.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(onCloseOthers()) );
    menu->addAction(action);
    //toolbar->addAction(W_ACTION_CLOSE_OTHERS, action);

    action = mActionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_ALL);
    action->setIcon(QIcon(":/close_all.png"));
    connect(         action, SIGNAL(triggered()),
             mCentralWidget, SLOT(onCloseAll()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_CLOSE_ALL, action);


    mMenus[W_ACTION_GROUP_FILE] = menu;




    menu = menuBar()->addMenu(tr("Edit"));

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_UNDO);
    action->setIcon(QIcon(":/undo.png"));
    connect(    action, SIGNAL(triggered()),
             editProxy, SLOT(onUndo()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_UNDO, action);

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_REDO);
    action->setIcon(QIcon(":/redo.png"));
    connect(    action, SIGNAL(triggered()),
             editProxy, SLOT(onRedo()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_REDO, action);

    menu->addSeparator();

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_CUT);
    action->setIcon(QIcon(":/cut.png"));
    connect(    action, SIGNAL(triggered()),
             editProxy, SLOT(onCut()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_CUT, action);

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_COPY);
    action->setIcon(QIcon(":/copy.png"));
    connect(    action, SIGNAL(triggered()),
             editProxy, SLOT(onCopy()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_COPY, action);

    action = mActionManager->getAction(W_ACTION_GROUP_EDIT, W_ACTION_PASTE);
    action->setIcon(QIcon(":/paste.png"));
    connect(    action, SIGNAL(triggered()),
             editProxy, SLOT(onPaste()) );
    menu->addAction(action);
    toolbar->addAction(W_ACTION_PASTE, action);

    mMenus[W_ACTION_GROUP_EDIT] = menu;




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




void MainWindow::openFile(const QString &file)
{
/*    if(!QFileInfo(str).exists()) {
        LOG_DEBUG("File not found.");
        continue;
    }

    files << QFileInfo(str).absoluteFilePath();
  */
    LOG_WARNING("file");
}

void MainWindow::onPopup1()
{
    Popup::popup("Test1", "Test very very very very very very long popup", this);
}

void MainWindow::onPopup2()
{
    Popup::popup("Test2", "Test cos tam cos tam long popup", this);
}

void MainWindow::onPopup3()
{
    Popup::popup("Test3", "Test very hello hello very long popup", this);
}

