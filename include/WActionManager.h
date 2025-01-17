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
#define W_ACTION_GROUP_SEARCH   "Search"
#define W_ACTION_GROUP_VIEW     "View"
#define W_ACTION_GROUP_TOOLS    "Tools"
#define W_ACTION_GROUP_MISC     "Misc"


    //W_ACTION_GROUP_FILE
#define W_ACTION_NEW            "New"
#define W_ACTION_OPEN           "Open"
#define W_ACTION_RELOAD         "Reload"
#define W_ACTION_SAVE           "Save"
#define W_ACTION_SAVE_AS        "Save_As"
#define W_ACTION_SAVE_ALL       "Save_All"

#define W_ACTION_CLOSE          "Close"
#define W_ACTION_CLOSE_ALL      "Close_All"
#define W_ACTION_CLOSE_OTHERS   "Close_Others"

#define W_ACTION_EXIT           "Exit"

    //W_ACTION_GROUP_EDIT
#define W_ACTION_UNDO           "Undo"
#define W_ACTION_REDO           "Redo"
#define W_ACTION_CUT            "Cut"
#define W_ACTION_COPY           "Copy"
#define W_ACTION_PASTE          "Paste"


    //W_ACTION_GROUP_SEARCH
#define W_ACTION_FIND           "Find"
#define W_ACTION_FIND_NEXT      "Find_Next"
#define W_ACTION_FIND_PREV      "Find_Prev"
#define W_ACTION_FIND_IN_FILES  "Find_In_Files"
#define W_ACTION_REPLACE        "Replace"

#define W_ACTION_JUMP_UP_STYLE1 "JumpUpStyle1"
#define W_ACTION_JUMP_UP_STYLE2 "JumpUpStyle2"
#define W_ACTION_JUMP_UP_STYLE3 "JumpUpStyle3"
#define W_ACTION_JUMP_UP_STYLE4 "JumpUpStyle4"
#define W_ACTION_JUMP_UP_STYLE5 "JumpUpStyle5"
#define W_ACTION_JUMP_DW_STYLE1 "JumpDwStyle1"
#define W_ACTION_JUMP_DW_STYLE2 "JumpDwStyle2"
#define W_ACTION_JUMP_DW_STYLE3 "JumpDwStyle3"
#define W_ACTION_JUMP_DW_STYLE4 "JumpDwStyle4"
#define W_ACTION_JUMP_DW_STYLE5 "JumpDwStyle5"


    //W_ACTION_GROUP_VIEW
#define W_ACTION_WCHARS         "WChars"
#define W_ACTION_WRAP           "Wrap"
#define W_ACTION_INDENT_GUIDE   "IndentGuide"
#define W_ACTION_ZOOM_DEF       "ZoomDef"
#define W_ACTION_ZOOM_IN        "ZoomIn"
#define W_ACTION_ZOOM_OUT       "ZoomOut"
#define W_ACTION_SYNC_V         "SyncV"
#define W_ACTION_SYNC_H         "SyncH"
#define W_ACTION_MONITOR_MODE   "MonitorMode"
#define W_ACTION_MINI_MAP       "MiniMap"

    //W_ACTION_GROUP_TOOLS
#define W_ACTION_CUSTOMIZE      "Customize"
#define W_ACTION_SETTINGS       "Settings"






#endif // __W_ACTION_MANAGER_H_
