/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       WActionManager.cpp
 *  @brief      Wolverine::ActionManager class implementation.
 */


#include "WActionManager.h"

#include <QAction>
#include <QApplication>
#include <QMutex>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>



using namespace Wolverine;


static ActionManager *sInstance = 0;


static void initializeActions();
static void deleteActionManagerInstance();


/**
 *  The ActionInitializer class
 */
class ActionInitializer : public QRunnable
{
public:
    void run()
    {
        initializeActions();
    }

};


static QMutex mutex;

static QThreadPool *sThreadPool = 0;
static bool isInitializationDone = false;


/**
 *  Default constructor.
 */
ActionManager::ActionManager()
{

    qAddPostRoutine(deleteActionManagerInstance);
}


/**
 *  Start initializing in separate thread.
 *
 *  Function should be called as soon as possible.
 */
//static
void ActionManager::instanceWithNewThread()
{
    if(sInstance == 0) {
        mutex.lock();
        if(sInstance == 0) {
            sInstance = new ActionManager();
            sThreadPool = QThreadPool::globalInstance();
            // Initializer is deleted automaticaly after finishing its job.
            sThreadPool->start(new ActionInitializer());
        }
        mutex.unlock();
    }
}



/**
 *  Creates instance of ActionManager class.
 *
 * @return
 */
//static
ActionManager* ActionManager::instance()
{
    if(sInstance == 0) {
        mutex.lock();
        if(sInstance == 0) {
            // Initialization not started yet, do it now
            sInstance = new ActionManager();
            initializeActions();
            mutex.unlock();
            return sInstance;
        }
        mutex.unlock();
    }

    if(!isInitializationDone) {
        mutex.lock();
        if(!isInitializationDone) {
            //Initialization pending, we have to wait
            sThreadPool->waitForDone();
        }
        mutex.unlock();
    }

    return sInstance;
}



/**
 *  Deletes ActionManager instance.
 *
 *  It is called just before application is exited.
 */
//static
void deleteActionManagerInstance()
{
    delete sInstance;
    sInstance = 0;
}



/**
 *  Initializes actions.
 *
 *  We cannot initialize icons here because we use non gui thread because of warning:
 *  "QPixmap: It is not safe to use pixmaps outside the GUI thread"
 *
 *  Icons are initialized when menu/toolbar is created.
 */
//static
void initializeActions()
{
    QAction *action;

    action = new QAction(QObject::tr("New"), 0);
    action->setShortcut(QObject::tr("Ctrl+N"));
    action->setStatusTip(QObject::tr("Create a new file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_NEW, action);

    action = new QAction(QObject::tr("Open..."), 0);
    action->setShortcut(QObject::tr("Ctrl+O"));
    action->setStatusTip(QObject::tr("Open existing file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_OPEN, action);


    action = new QAction(QObject::tr("Close"), 0);
    action->setShortcut(QObject::tr("Ctrl+W"));
    action->setStatusTip(QObject::tr("Close current file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE, action);

    action = new QAction(QObject::tr("Close Others"), 0);
    //action->setShortcut(QObject::tr());
    action->setStatusTip(QObject::tr("Close other files"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_OTHERS, action);

    action = new QAction(QObject::tr("Close All"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+W"));
    action->setStatusTip(QObject::tr("Close all files"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_CLOSE_ALL, action);




    action = new QAction(QObject::tr("Undo"), 0);
    action->setShortcut(QObject::tr("Ctrl+Z"));
    action->setStatusTip(QObject::tr("Undo action"));
    sInstance->addAction(W_ACTION_GROUP_EDIT, W_ACTION_UNDO, action);


    action = new QAction(QObject::tr("Customize"), 0);
    //action->setShortcut(QObject::tr("Ctrl+Alt+S"));
    action->setStatusTip(QObject::tr("Enable/disable customization"));
    action->setCheckable(true);
    sInstance->addAction(W_ACTION_GROUP_TOOLS, W_ACTION_CUSTOMIZE, action);

    action = new QAction(QObject::tr("Settings"), 0);
    //action->setShortcut(QObject::tr("Ctrl+Alt+S"));
    action->setStatusTip(QObject::tr("Settings dialog"));
    sInstance->addAction(W_ACTION_GROUP_TOOLS, W_ACTION_SETTINGS, action);




    action = new QAction(QObject::tr("Move to Left"), 0);
    //action->setShortcut(QObject::tr("Ctrl+Alt+S"));
    action->setStatusTip(QObject::tr("Move tab to left panel"));
    sInstance->addAction(W_ACTION_GROUP_MISC, W_ACTION_MOVE_LEFT, action);

    action = new QAction(QObject::tr("Move to Right"), 0);
    //action->setShortcut(QObject::tr("Ctrl+Alt+S"));
    action->setStatusTip(QObject::tr("Move tab to right panel"));
    sInstance->addAction(W_ACTION_GROUP_MISC, W_ACTION_MOVE_RIGHT, action);




    sInstance->addScheme("VimCommand");
    sInstance->addScheme("VimInput");
    sInstance->addScheme("VimVisible");

    sInstance->setScheme("Default");

    sInstance->restoreConfig();

    isInitializationDone = true;
}
