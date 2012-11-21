

#include "WActionManager.h"

#include <QAction>
#include <QApplication>



using namespace Wolverine;


ActionManager* ActionManager::mInstance = 0;


//*************************************************************************************************
/** \brief  Default constructor.
*
**************************************************************************************************/
ActionManager::ActionManager()
{
    initialize();

    qAddPostRoutine(deleteInstance);
}


ActionManager* ActionManager::instance()
{
    if(mInstance == 0)
        mInstance = new ActionManager();
    return mInstance;
}

void ActionManager::deleteInstance()
{
    delete mInstance;
    mInstance = 0;
}





//*************************************************************************************************
/** \brief  Initializes actions
*
**************************************************************************************************/
void ActionManager::initialize()
{
    QAction *action;

    action = new QAction(QIcon(":/new.png"), tr("New"), this);
    action->setShortcut(tr("Ctrl+N"));
    action->setStatusTip(tr("Create a new file"));
    addAction(W_ACTION_GROUP_FILE, W_ACTION_NEW, action);

    action = new QAction(QIcon(":/open.png"), tr("Open"), this);
    action->setShortcut(tr("Ctrl+O"));
    action->setStatusTip(tr("Open existing file"));
    addAction(W_ACTION_GROUP_FILE, W_ACTION_OPEN, action);


    action = new QAction(QIcon(":/undo.png"), tr("Undo"), this);
    action->setShortcut(tr("Ctrl+Z"));
    action->setStatusTip(tr("Undo action"));
    addAction(W_ACTION_GROUP_EDIT, W_ACTION_UNDO, action);


    action = new QAction(QIcon(":/settings.png"), tr("Settings"), this);
    //action->setShortcut(tr("Ctrl+Alt+S"));
    action->setStatusTip(tr("Settings dialog"));
    addAction(W_ACTION_GROUP_TOOLS, W_ACTION_SETTINGS, action);


}
