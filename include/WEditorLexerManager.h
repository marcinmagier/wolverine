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
 *  @file       WEditorLexerManager.h
 *  @brief      Wolverine::EditorLexerManager class interface.
 */




#ifndef __W_EDITOR_LEXER_MANAGER_H_
 #define __W_EDITOR_LEXER_MANAGER_H_


#include <QObject>


class QStringList;

namespace Wolverine
{


class EditorLexerManager : public QObject
{
    Q_OBJECT

private:
    explicit EditorLexerManager();

public:
    static EditorLexerManager* instance();

    //void saveConfig();
    //void restoreConfig();
    void createConfigurationBackup();
    void restoreConfigurationBackup();
    void dropConfigurationBackup();
    QWidget* getLexerManagerWidget(QWidget *parent = 0);


private:
    static const QStringList sLexerList;
};



}

#endif // __W_EDITOR_LEXER_MANAGER_H_
