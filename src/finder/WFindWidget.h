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
 *  @file       WFindWidget.h
 *  @brief      Wolverine::FindWidget class interface.
 */


#ifndef __W_FIND_WIDGET_H_
 #define __W_FIND_WIDGET_H_


#include "WFindRequest.h"

#include <QDockWidget>


class GeneralSettings;


namespace Ui {
class FindWidget;
}


namespace Wolverine
{

class Finder;


class FindWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    enum Idx {
        FindIdx,
        ReplaceIdx,
        FindInFilesIdx
    };


    explicit FindWidget(Finder *finder, QWidget *parent = 0);
    ~FindWidget();

    FindRequest getFindRequest();

    
private:
    void setupFindWidget();
    void setupReplaceWidget();
    void setupFindInFilesWidget();
    QString getCurrentEditorDir();

    Finder *mFinder;
    GeneralSettings *mGenSettings;

    Ui::FindWidget *ui;
};


}

#endif // __W_FIND_WIDGET_H_
