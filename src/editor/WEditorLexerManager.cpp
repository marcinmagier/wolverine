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
#include "WEditorLexerCfg.h"
#include "WEditorLexerManagerWidget.h"

#include "Logger.h"

#include "Qsci/qscilexer.h"
#include "Qsci/qscilexercpp.h"
#include "Qsci/qscilexerpython.h"

#include <QWidget>
#include <QStringList>
#include <QAction>
#include <QApplication>
#include <QSettings>
#include <QFileInfo>


#include <QDebug>




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
    mLexerMap = new QMap<QString, EditorLexerCfg*>();
    initializeLexers();
}

EditorLexerManager::~EditorLexerManager()
{
    saveConfig();

    foreach(EditorLexerCfg *eLexer, mLexerMap->values()) {
        delete eLexer;
    }
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



QString EditorLexerManager::getLexerName(QFileInfo *fileInfo)
{
    if(!fileInfo->exists())
        return QString("Normal Text");

    return QString("C++");
}


QsciLexer* EditorLexerManager::getLexer(const QString &lexName)
{
    if(!mLexerMap->contains(lexName))
        LOG_ERROR("Lexer not known!");

    EditorLexerCfg *eLexer = mLexerMap->value(lexName);
    if(eLexer->lexer)
        return eLexer->lexer;

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");
    qset.beginGroup(lexName);
    eLexer->createFunction(eLexer, &qset);
    qset.endGroup();
    return eLexer->lexer;
}




void EditorLexerManager::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");

    if(!qset.isWritable())
        return;

    foreach(QString lexName, mLexerMap->keys()) {
        qset.beginGroup(lexName);
        EditorLexerCfg *eLexer = mLexerMap->value(lexName);
        qset.setValue( "available", QVariant::fromValue( eLexer->isAvailable) );
        if(eLexer->lexer && eLexer->saveFunction) {
            eLexer->saveFunction(eLexer, &qset);
        }
        qset.endGroup();
    }
}


void EditorLexerManager::restoreBasicConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");

    foreach(QString lexName, mLexerMap->keys()) {
        qset.beginGroup(lexName);
        EditorLexerCfg *eLexer = mLexerMap->value(lexName);
        if(qset.contains("available"))
            eLexer->isAvailable = qset.value("available").toBool();
        qset.endGroup();
    }
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
    return new EditorLexerManagerWidget(mLexerMap, parent);
}






void EditorLexerManager::initializeLexers()
{
    EditorLexerCfg *eLexer;

    eLexer = new EditorLexerCfg(&createLexPython, &saveLexPython, true);
    mLexerMap->insert("Normal Text", eLexer);

    eLexer = new EditorLexerCfg(&createLexCPP, &saveLexCPP);
    mLexerMap->insert("C++", eLexer);

    eLexer = new EditorLexerCfg(0, 0);
    mLexerMap->insert("Java", eLexer);

    eLexer = new EditorLexerCfg(&createLexPython, &saveLexPython);
    mLexerMap->insert("Python", eLexer);

    restoreBasicConfig();
}

