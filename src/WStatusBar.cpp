/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       WStatusBar.cpp
 *  @brief      Wolverine::StatusBar class implementation.
 */


#include "WStatusBar.h"
#include "WEditor.h"
#include "WEditorProxy.h"


#include "CfgAppSettings.h"


using namespace Wolverine;


StatusBar::StatusBar(EditorProxy *currentEditor, QWidget *parent) :
    QStatusBar(parent),
    mCurrentEditor(currentEditor)
{

}




void StatusBar::onCurrentEditorChanged(Editor *editor)
{
    if(editor != mCurrentEditor) {

    }
}
