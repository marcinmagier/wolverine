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


class QLabel;
class QtLabel;
class QMouseEvent;

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

    void onClicked(QMouseEvent *event);
    void onClickedLong(QMouseEvent *event);
    void onDoubleClicked(QMouseEvent *event);


private:
    EditorProxy *mCurrentEditor;

    QtLabel *mLblFilePath;
    QLabel *mLblFileStatistics;
    QLabel *mLblPosition;
    QLabel *mLblCodec;
    QLabel *mLblLexer;
    QLabel *mLblEoL;
    QLabel *mLblInsOvr;


};


}

#endif // __W_STATUS_BAR_H_
