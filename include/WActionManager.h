/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       WActionManager.h
 *  @brief      Wolverine::ActionManager class interface.
 */

#ifndef __W_ACTION_MANAGER_H_
 #define __W_ACTION_MANAGER_H_


#include "qtactionmanager.h"

#include <QObject>



namespace Wolverine
{

class ActionManager : public QObject, public QtActionManager
{
    Q_OBJECT

private:
    ActionManager();

public:
    static void instanceWithNewThread();
    static ActionManager* instance();

    
signals:
    
public slots:

private:
    
};


}


#define W_ACTION_GROUP_GENERAL  "General"
#define W_ACTION_GROUP_FILE     "File"
#define W_ACTION_GROUP_EDIT     "Edit"
#define W_ACTION_GROUP_TOOLS    "Tools"


    //W_ACTION_GROUP_FILE
#define W_ACTION_NEW            "New"
#define W_ACTION_OPEN           "Open"
#define W_ACTION_SAVE           "Save"
#define W_ACTION_SAVE_AS        "Save_As"
#define W_ACTION_SAVE_ALL       "Save_All"

#define W_ACTION_CLOSE          "Close"
#define W_ACTION_CLOSE_ALL      "Close_All"
#define W_ACTION_CLOSE_OTHERS   "Close_Others"

    //W_ACTION_GROUP_EDIT
#define W_ACTION_UNDO           "Undo"
#define W_ACTION_REDO           "Redo"
#define W_ACTION_CUT            "Cut"
#define W_ACTION_COPY           "Copy"
#define W_ACTION_PASTE          "Paste"

    //W_ACTION_GROUP_TOOLS
#define W_ACTION_SETTINGS       "Settings"




#define W_ACTION_MOVE_LEFT      "Move_Left"
#define W_ACTION_MOVE_RIGHT     "Move_Right"



#endif // __W_ACTION_MANAGER_H_
