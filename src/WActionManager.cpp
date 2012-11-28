

#include "WActionManager.h"

#include <QAction>
#include <QApplication>
#include <QMutex>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
#include <QDebug>



using namespace Wolverine;



static void initializeActions();
static void deleteActionManagerInstance();


/**
 *  The Initializer class
 */
class Initializer : public QRunnable
{
public:
    void run()
    {
        qDebug() << "Init" << QThread::currentThread();
        initializeActions();
    }

};


static QMutex mutex;
static ActionManager *sInstance = 0;
static QThreadPool *sThreadPool = 0;
static Initializer *sInitializer = 0;


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
void ActionManager::instanceWithNewThread()
{
    if(sInstance == 0) {
        mutex.lock();
        if(sInstance == 0) {
            sInstance = new ActionManager();
            sInitializer = new Initializer();
            sInitializer->setAutoDelete(false);
            sThreadPool = QThreadPool::globalInstance();
            sThreadPool->start(sInitializer);
            qDebug() << QThread::currentThread();
        }
        mutex.unlock();
    }
}



/**
 *  Creates instance of ActionManager class.
 *
 * @return
 */
ActionManager* ActionManager::instance()
{
    if(sInstance == 0) {
        mutex.lock();
        if(sInstance == 0) {
            sInstance = new ActionManager();
            initializeActions();
            mutex.unlock();
            return sInstance;
        }
        mutex.unlock();
    }

    if(sInitializer) {
        mutex.lock();
        if(sInitializer) {
            //Initialization pending, we have to wait
            sThreadPool->waitForDone();
            delete sInitializer;
            sInitializer = 0;
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
static void deleteActionManagerInstance()
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
static void initializeActions()
{
    QAction *action;

    action = new QAction(QObject::tr("New"), 0);
    action->setShortcut(QObject::tr("Ctrl+N"));
    action->setStatusTip(QObject::tr("Create a new file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_NEW, action);

    action = new QAction(QObject::tr("Open"), 0);
    action->setShortcut(QObject::tr("Ctrl+O"));
    action->setStatusTip(QObject::tr("Open existing file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_OPEN, action);


    action = new QAction(QObject::tr("Undo"), 0);
    action->setShortcut(QObject::tr("Ctrl+Z"));
    action->setStatusTip(QObject::tr("Undo action"));
    sInstance->addAction(W_ACTION_GROUP_EDIT, W_ACTION_UNDO, action);


    action = new QAction(QObject::tr("Settings"), 0);
    //action->setShortcut(QObject::tr("Ctrl+Alt+S"));
    action->setStatusTip(QObject::tr("Settings dialog"));
    sInstance->addAction(W_ACTION_GROUP_TOOLS, W_ACTION_SETTINGS, action);



    sInstance->addScheme("VimCommand");
    sInstance->addScheme("VimInput");
    sInstance->addScheme("VimVisible");

    sInstance->setScheme("Default");

    sInstance->restoreConfig();
}
