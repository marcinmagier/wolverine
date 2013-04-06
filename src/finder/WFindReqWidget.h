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



#ifndef __W_FIND_REQ_WIDGET_H_
 #define __W_FIND_REQ_WIDGET_H_


#include "WFindOptions.h"

#include <QStackedWidget>


class GeneralSettings;


namespace Ui {
class FindReqWidget;
}


namespace Wolverine {


class Finder;


class FindReqWidget : public QStackedWidget
{
    Q_OBJECT
    
    enum Idx {
        FindIdx,
        ReplaceIdx,
        FindInFilesIdx
    };


public:
    explicit FindReqWidget(Finder *finder, QWidget *parent = 0);
    ~FindReqWidget();

    FindOptions getFindOptions();

    void setInitialSearchPattern(const QString &pattern);
    void setInitialReplacePattern(const QString &pattern);
    void setInitialFilters(const QString &filters);
    void setInitialDirectory(const QString &directory);


private slots:
    void onCurrentChanged(int idx);
    

private:
    void setupFindWidget();
    void setupReplaceWidget();
    void setupFindInFilesWidget();

    Finder *mFinder;
    GeneralSettings *mGenSettings;

    Ui::FindReqWidget *ui;
};


};

#endif // __W_FIND_REQ_WIDGET_H_
