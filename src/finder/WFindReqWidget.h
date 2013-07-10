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
 *  @file       WFindReqWidget.h
 *  @brief      Wolverine::FindReqWidget class interface.
 */


#ifndef __W_FIND_WIDGET_H_
 #define __W_FIND_WIDGET_H_


#include "WFindRequest.h"

#include <QWidget>


class GeneralSettings;


namespace Ui {
class FindReqWidget;
}


namespace Wolverine
{

class Finder;


class FindReqWidget : public QWidget
{
    Q_OBJECT
    
public:
    enum Idx {
        FindIdx,
        ReplaceIdx,
        FindInFilesIdx
    };


    explicit FindReqWidget(Finder *finder, QWidget *parent = 0);
    ~FindReqWidget();

    void setCurrentIndex(Idx idx);
    Idx getCurrentIndex();
    FindRequest getFindRequest();

    void setInitialSearchPattern(const QString &pattern);
    void setInitialReplacePattern(const QString &pattern);
    void setInitialFilters(const QString &pattern);
    void setInitialDirectory(const QString &pattern);

    void updateSearchHistory();
    void updateReplaceHistory();
    void updateFilterAndDirectoryHistory();

    
private slots:
    void onSelectDirectoryClicked();
    void onCurrentDirectoryClicked();
    void onSearchEditReturnPressed();
    void onReplaceEditReturnPressed();


private:
    void setupFindWidget();
    void setupReplaceWidget();
    void setupFindInFilesWidget();
    QString getCurrentEditorDir();

    Idx mIdx;
    Finder *mFinder;
    GeneralSettings *mGenSettings;

    Ui::FindReqWidget *ui;
};


}

#endif // __W_FIND_WIDGET_H_
