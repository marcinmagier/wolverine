/**************************************************************************************************
**
**  Copyright (C) 2012-2013 Magier Marcin
**
**  This program is free software: you can redistribute it and/or modify it under the terms
**  of the GNU General Public License as published by the Free Software Foundation,
**  either version 3 of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
**  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**  See the GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************************************/

/**
 *  @file       WFinder.h
 *  @brief      Wolverine::Finder class interface.
 */




#ifndef __W_FINDER_H_
 #define __W_FINDER_H_


#include <QObject>
#include <QPoint>

class QAction;
class QDockWidget;
class QtDockWidget;

namespace Wolverine
{

class FindRequest;
class FindResults;
class FindReqWidget;
class FindResWidget;
class Editor;
class EditorProxy;

class CentralWidget;

class Finder: public QObject
{
    Q_OBJECT

    explicit Finder();
    virtual ~Finder();


public:
    static Finder* instance();
    static void deleteInstance();

    void setFindAction(QAction *action);
    void setReplaceAction(QAction *action);
    void setFindInFilesAction(QAction *action);

    void setCentralWidget(CentralWidget* central);

    QDockWidget* getFindReqDock();
    QDockWidget* getFindResDock();


public slots:
    void showFindWidget();
    void showFindInFilesWidget();
    void showReplaceWidget();

    void findNext();
    void findPrev();
    void findAll();
    void findInAllTabs();
    void findInFiles();

    void replace();
    void replaceFindNext();
    void replaceAll();
    void replaceInAllTabs();
    void replaceInFiles();


    void markAll();
    void markAll(int style);
    void unmarkAll();
    void unmarkAll(int style);
    void jumpNextMark();
    void jumpNextMark(int style);
    void jumpPrevMark();
    void jumpPrevMark(int style);


private slots:
    void onReqDockVisibilityChanged(bool visible);
    void onReqDockCustomContextMenuRequested(const QPoint &pos);

    void onResDockVisibilityChanged(bool visible);


    void onEditorChanged(Editor *edit);
    void onEditorNotValid(Editor *edit);
    void onEditorSelectionChanged();
    void onEditorCursorPositionChanged(int line, int index);


private:
    void setupFindWidget();
    void createResultsWidget();
    void find(const FindRequest &req, bool reverse);
    FindResults* find(const FindRequest &req);

    QtDockWidget *mDockReqWidget;
    QtDockWidget *mDockResWidget;
    FindReqWidget *mFindReqWidget;
    FindResWidget *mFindResWidget;
    FindResults *mFindResults;
    EditorProxy *mEditorProxy;
    QAction *mFindAction;
    QAction *mFindInFilesAction;
    QAction *mReplaceAction;

    CentralWidget *mCentralWidget;

    static Finder *sInstance;


    friend class FindResWidget;
};


}

#endif // __W_FINDER_H_
