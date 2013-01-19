/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       WStatusBar.h
 *  @brief      Wolverine::StatusBar class interface.
 */

#ifndef __W_STATUS_BAR_H_
 #define __W_STATUS_BAR_H_


#include <QStatusBar>



namespace Wolverine
{

class Editor;
class EditorProxy;


class StatusBar : public QStatusBar
{
    Q_OBJECT

public:
    StatusBar(EditorProxy *currentEditor, QWidget *parent=0);


private slots:
    void onCurrentEditorChanged(Editor *editor);


private:
    EditorProxy *mCurrentEditor;

};


}

#endif // __W_STATUS_BAR_H_
