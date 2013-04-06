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

class QDockWidget;
class QAction;


namespace Wolverine
{

class FindOptions;
class FindReqDock;
class FindReqWidget;
class EditorProxy;

class Finder: public QObject
{
    Q_OBJECT

    explicit Finder();
    virtual ~Finder();


public:
    static Finder* instance();
    static void deleteInstance();


public slots:
    void showFindWidget(bool visible);
    void showFindInFilesWidget(bool visible);
    void showReplaceWidget(bool visible);

    void findNext();
    void findNext(FindOptions *opt);
    void findPrev();
    void findPrev(FindOptions *opt);
    void findAll();
    void findAll(FindOptions *opt);
    void findInAllTabs();
    void findInAllTabs(FindOptions *opt);


    void markAll();


signals:
    void showWidgetRequested(QDockWidget *widget, Qt::DockWidgetArea area, QString title);


private slots:
    void onCloseRequested();
    void onCustomContextMenuRequested(const QPoint &pos);


private:
    void createFindWidget();

    FindReqDock *mFindRequestDock;
    FindReqWidget *mFindReqWidget;
    EditorProxy *mEditorProxy;
    QAction *mFindAction;
    QAction *mFindInFilesAction;
    QAction *mReplaceAction;

    static Finder *sInstance;
};


}

#endif // __W_FINDER_H_
