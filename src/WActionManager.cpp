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
    action->setShortcut(QKeySequence::New);
    action->setStatusTip(QObject::tr("Create a new file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_NEW, action);

    action = new QAction(QObject::tr("Open..."), 0);
    action->setShortcut(QKeySequence::Open);
    action->setStatusTip(QObject::tr("Open existing file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_OPEN, action);

    action = new QAction(QObject::tr("Reload"), 0);
    action->setShortcut(QKeySequence::Refresh);
    action->setStatusTip(QObject::tr("Reload file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_RELOAD, action);

    action = new QAction(QObject::tr("Save"), 0);
    action->setShortcut(QKeySequence::Save);
    action->setStatusTip(QObject::tr("Save file"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE, action);

    action = new QAction(QObject::tr("Save As..."), 0);
    action->setShortcut(QKeySequence::SaveAs);
    action->setStatusTip(QObject::tr("Save file as ..."));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE_AS, action);

    action = new QAction(QObject::tr("Save All"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+S"));
    action->setStatusTip(QObject::tr("Save all files"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_SAVE_ALL, action);

    action = new QAction(QObject::tr("Close"), 0);
    action->setShortcut(QKeySequence::Close);
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

    action = new QAction(QObject::tr("Exit"), 0);
    action->setShortcut(QKeySequence::Quit);
    action->setStatusTip(QObject::tr("Close application"));
    sInstance->addAction(W_ACTION_GROUP_FILE, W_ACTION_EXIT, action);



    action = new QAction(QObject::tr("Undo"), 0);
    action->setShortcut(QKeySequence::Undo);
    //action->setStatusTip(QObject::tr("Undo action"));
    sInstance->addAction(W_ACTION_GROUP_EDIT, W_ACTION_UNDO, action);

    action = new QAction(QObject::tr("Redo"), 0);
    action->setShortcut(QKeySequence::Redo);
    //action->setStatusTip(QObject::tr("Redo action"));
    sInstance->addAction(W_ACTION_GROUP_EDIT, W_ACTION_REDO, action);

    action = new QAction(QObject::tr("Cut"), 0);
    action->setShortcut(QKeySequence::Cut);
    //action->setStatusTip(QObject::tr("Cut selection"));
    sInstance->addAction(W_ACTION_GROUP_EDIT, W_ACTION_CUT, action);

    action = new QAction(QObject::tr("Copy"), 0);
    action->setShortcut(QKeySequence::Copy);
    //action->setStatusTip(QObject::tr("Copy selection"));
    sInstance->addAction(W_ACTION_GROUP_EDIT, W_ACTION_COPY, action);

    action = new QAction(QObject::tr("Paste"), 0);
    action->setShortcut(QKeySequence::Paste);
    //action->setStatusTip(QObject::tr("Paste"));
    sInstance->addAction(W_ACTION_GROUP_EDIT, W_ACTION_PASTE, action);



    action = new QAction(QObject::tr("Find"), 0);
    action->setShortcut(QKeySequence::Find);
    //action->setStatusTip(QObject::tr("Find"));
    action->setCheckable(true);
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND, action);

    action = new QAction(QObject::tr("Find Next"), 0);
    action->setShortcut(QKeySequence::FindNext);
    //action->setStatusTip(QObject::tr("Find Next"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_NEXT, action);

    action = new QAction(QObject::tr("Find Previous"), 0);
    action->setShortcut(QKeySequence::FindPrevious);
    //action->setStatusTip(QObject::tr("Find"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_PREV, action);

    action = new QAction(QObject::tr("Find In Files"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+F"));
    //action->setStatusTip(QObject::tr("Find"));
    action->setCheckable(true);
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_FIND_IN_FILES, action);

    action = new QAction(QObject::tr("Replace"), 0);
    action->setShortcut(QKeySequence::Replace);
    //action->setStatusTip(QObject::tr("Find"));
    action->setCheckable(true);
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_REPLACE, action);


    action = new QAction(QObject::tr("1st Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+1"));
    action->setData(1);
    //action->setStatusTip(QObject::tr("1st Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE1, action);

    action = new QAction(QObject::tr("2nd Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+2"));
    action->setData(2);
    //action->setStatusTip(QObject::tr("2nd Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE2, action);

    action = new QAction(QObject::tr("3rd Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+3"));
    action->setData(3);
    //action->setStatusTip(QObject::tr("3rd Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE3, action);

    action = new QAction(QObject::tr("4th Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+4"));
    action->setData(4);
    //action->setStatusTip(QObject::tr("4st Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE4, action);

    action = new QAction(QObject::tr("5th Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+5"));
    action->setData(5);
    //action->setStatusTip(QObject::tr("5st Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_UP_STYLE5, action);

    action = new QAction(QObject::tr("1st Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+1"));
    action->setData(1);
    //action->setStatusTip(QObject::tr("1st Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE1, action);

    action = new QAction(QObject::tr("2nd Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+2"));
    action->setData(2);
    //action->setStatusTip(QObject::tr("2nd Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE2, action);

    action = new QAction(QObject::tr("3rd Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+3"));
    action->setData(3);
    //action->setStatusTip(QObject::tr("3rd Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE3, action);

    action = new QAction(QObject::tr("4th Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+4"));
    action->setData(4);
    //action->setStatusTip(QObject::tr("4st Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE4, action);

    action = new QAction(QObject::tr("5th Style"), 0);
    action->setShortcut(QObject::tr("Ctrl+Shift+5"));
    action->setData(5);
    //action->setStatusTip(QObject::tr("5st Style"));
    sInstance->addAction(W_ACTION_GROUP_SEARCH, W_ACTION_JUMP_DW_STYLE5, action);





    action = new QAction(QObject::tr("Show White Chars"), 0);
    //action->setShortcut(QObject::tr("Ctrl+C"));
    //action->setStatusTip(QObject::tr("Show White Chars"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_WCHARS, action);

    action = new QAction(QObject::tr("Wrap Lines"), 0);
    //action->setShortcut(QObject::tr("Ctrl+V"));
    //action->setStatusTip(QObject::tr("Wrap Lines"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_WRAP, action);

    action = new QAction(QObject::tr("Show Indent Guide"), 0);
    //action->setShortcut(QObject::tr("Ctrl+V"));
    //action->setStatusTip(QObject::tr("Wrap Lines"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_INDENT_GUIDE, action);

    action = new QAction(QObject::tr("Zoom In"), 0);
    action->setShortcut(QKeySequence::ZoomIn);
    //action->setStatusTip(QObject::tr("Zoom in"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_ZOOM_IN, action);

    action = new QAction(QObject::tr("Zoom Out"), 0);
    action->setShortcut(QKeySequence::ZoomOut);
    //action->setStatusTip(QObject::tr("Zoom out"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_ZOOM_OUT, action);

    action = new QAction(QObject::tr("Zoom Default"), 0);
    action->setShortcut(QObject::tr("Ctrl+/"));
    //action->setStatusTip(QObject::tr("Zoom Default"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_ZOOM_DEF, action);

    action = new QAction(QObject::tr("Synchronize Vertical Scrolling"), 0);
    //action->setShortcut(QObject::tr("Ctrl+V"));
    //action->setStatusTip(QObject::tr("Wrap Lines"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_SYNC_V, action);

    action = new QAction(QObject::tr("Synchronize Horizontal Scrolling"), 0);
    //action->setShortcut(QObject::tr("Ctrl+V"));
    //action->setStatusTip(QObject::tr("Wrap Lines"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_SYNC_H, action);

    action = new QAction(QObject::tr("Monitor Mode"), 0);
    //action->setShortcut(QObject::tr("Ctrl+V"));
    action->setStatusTip(QObject::tr("Automatically reload if file was changed externally"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_MONITOR_MODE, action);

    action = new QAction(QObject::tr("Mini Map"), 0);
    //action->setShortcut(QObject::tr("Ctrl+V"));
    action->setStatusTip(QObject::tr("Mini Map"));
    sInstance->addAction(W_ACTION_GROUP_VIEW, W_ACTION_MINI_MAP, action);



    action = new QAction(QObject::tr("Customize"), 0);
    //action->setShortcut(QObject::tr("Ctrl+Alt+S"));
    action->setStatusTip(QObject::tr("Enable/disable customization"));
    action->setCheckable(true);
    sInstance->addAction(W_ACTION_GROUP_TOOLS, W_ACTION_CUSTOMIZE, action);

    action = new QAction(QObject::tr("Settings"), 0);
    action->setShortcut(QKeySequence::Preferences);
    action->setStatusTip(QObject::tr("Settings dialog"));
    sInstance->addAction(W_ACTION_GROUP_TOOLS, W_ACTION_SETTINGS, action);





   // sInstance->addScheme("VimCommand");
 //   sInstance->addScheme("VimInput");
  //  sInstance->addScheme("VimVisible");

    sInstance->setScheme("Default");

    sInstance->restoreConfig();

    isInitializationDone = true;
}
