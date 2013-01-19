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
 *  @file       WEditorLexerManager.cpp
 *  @brief      Wolverine::EditorLexerManager class implementation.
 */




#include "WEditorLexerManager.h"

#include <QWidget>
#include <QStringList>
#include <QAction>
#include <QApplication>


using namespace Wolverine;


static void deleteEditorLexerManagerInstance();

static EditorLexerManager *sInstance = 0;


/**
 *  Constructor
 */
EditorLexerManager::EditorLexerManager() :
    QObject()
{
    qAddPostRoutine(deleteEditorLexerManagerInstance);
}


/**
 *  Creates instance of EditorLexerManager class.
 * @return
 */
//static
EditorLexerManager* EditorLexerManager::instance()
{
    if(sInstance == 0)
        sInstance = new EditorLexerManager();
    return sInstance;
}


/**
 *  Deletes instance of EditorLexerManager
 */
//static
void deleteEditorLexerManagerInstance()
{
    delete sInstance;
    sInstance = 0;
}




void EditorLexerManager::createConfigurationBackup()
{

}

void EditorLexerManager::restoreConfigurationBackup()
{

}

void EditorLexerManager::dropConfigurationBackup()
{

}

QWidget* EditorLexerManager::getLexerManagerWidget(QWidget *parent)
{
    return new QWidget(parent);
}


QActionList EditorLexerManager::getLexerActions()
{
    return mLexerActions;
}



void EditorLexerManager::initializeActions()
{
    QAction *action;
    action = new QAction(QString("Bash"), 0);
    mLexerActions.append(action);

    action = new QAction(QString("Batch"), 0);
    mLexerActions.append(action);

    action = new QAction(QString("C++"), 0);
    mLexerActions.append(action);

    action = new QAction(QString("C#"), 0);
    mLexerActions.append(action);

    action = new QAction(QString("HTML"), 0);
    mLexerActions.append(action);

    action = new QAction(QString("Java"), 0);
    mLexerActions.append(action);

    action = new QAction(QString("Makefile"), 0);
    mLexerActions.append(action);

    action = new QAction(QString("Python"), 0);
    mLexerActions.append(action);
}
