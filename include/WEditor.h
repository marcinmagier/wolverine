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
 *  @file       WEditor.h
 *  @brief      Wolverine::Editor class interface.
 */




#ifndef __W_EDITOR_H_
 #define __W_EDITOR_H_


#include "qtscintilla.h"


class ScintillaSettings;

namespace Wolverine
{

class EditorBinder;
class EditorLexerManager;

class Editor: public QtScintilla
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    explicit Editor(EditorBinder *doc, QWidget *parent = 0);
    virtual ~Editor();

    Editor* getLinkedCopy();
    static void removeEditor(Editor *editor);

    void setBinder(EditorBinder* doc);
    EditorBinder* getBinder();


signals:
    void focusReceived();


protected:
    virtual void focusInEvent(QFocusEvent *event);

private slots:
    void onCursorLineChanged(int line);
    void onShowLineNumbersEnabledChanged(bool val);


private:
    void initialize();
    void updateLineNoMargin(bool visible);

    EditorBinder *mBinder;
    static EditorLexerManager mLexerManager;
    ScintillaSettings *mSettings;

};



}

#endif // __W_EDITOR_H_
