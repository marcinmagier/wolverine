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
class QFileInfo;
class QMainWindow;

#include "WEditor.h"

namespace Wolverine
{

class EditorProxy;


class StatusBar : public QStatusBar
{
    Q_OBJECT

public:
    StatusBar(EditorProxy *currentEditor, QWidget *parent);


private slots:
    void onCurrentEditorChanged(Editor *editor);
    void onCurrentEditorPosChanged(int line, int column);
    void onCurrentEditorTextChanged();
    void onCurrentEditorSelectionChanged();
    void onCurrentEditorFileInfoChanged(QFileInfo *fileinfo);
    void onCurrentEditorLexerChanged(const QString &name);
    void onCurrentEditorEolChanged(Editor::EolMode eolMode);

    void onLblCodecClickLong(Qt::MouseButton button);
    void onLblLexerClickLong(Qt::MouseButton button);
    void onLblEoLClickLong(Qt::MouseButton button);
    void onLblInsOvrDoubleClick(Qt::MouseButton button);


private:


    EditorProxy *mEditorProxy;

    QMainWindow *mMainWindow;
    QtLabel *mLblFilePath;
    QtLabel *mLblFileStatistics;
    QtLabel *mLblPosition;
    QtLabel *mLblCodec;
    QtLabel *mLblLexer;
    QtLabel *mLblEoL;
    QtLabel *mLblInsOvr;


};


}

#endif // __W_STATUS_BAR_H_
