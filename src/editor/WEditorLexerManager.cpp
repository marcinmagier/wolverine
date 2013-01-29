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

#include "qscilexer.h"
#include "qscilexercpp.h"
#include "qscilexerpython.h"

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
    mLexerMap = new EditorLexerCfgMap();
    mLexerMapBackup = 0;
    initializeLexers();
}

EditorLexerManager::~EditorLexerManager()
{
    dropConfigurationBackup();

    foreach(EditorLexerCfg *eLexer, mLexerMap->values()) {
        delete eLexer;
    }
    delete mLexerMap;
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

    foreach(const QString &lexName, mLexerMap->keys()) {
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

    foreach(const QString &lexName, mLexerMap->keys()) {
        qset.beginGroup(lexName);
        EditorLexerCfg *eLexer = mLexerMap->value(lexName);
        if(qset.contains("available"))
            eLexer->isAvailable = qset.value("available").toBool();
        qset.endGroup();
    }
}




void EditorLexerManager::createConfigurationBackup()
{
    dropConfigurationBackup();
    mLexerMapBackup = new EditorLexerCfgMap();
    foreach(const QString &lexName, mLexerMap->keys()) {
        this->getLexer(lexName);    //We have to create all lexers to have backup
        EditorLexerCfg *old = mLexerMap->value(lexName);
        EditorLexerCfg *eLexer = new EditorLexerCfg(old->createFunction, old->saveFunction, old->copyFunction, old->isAvailable);
        old->copyFunction(old, eLexer);
        mLexerMapBackup->insert(lexName, eLexer);
    }
}

void EditorLexerManager::restoreConfigurationBackup()
{
    foreach(const QString &lexName, mLexerMap->keys()) {
        EditorLexerCfg *origin = mLexerMap->value(lexName);
        EditorLexerCfg *backup = mLexerMapBackup->value(lexName);
        origin->copyFunction(backup, origin);
    }
}

void EditorLexerManager::dropConfigurationBackup()
{
    if(mLexerMapBackup) {
        foreach(EditorLexerCfg *eLexer, mLexerMapBackup->values()) {
            delete eLexer;
        }
        delete mLexerMapBackup;
        mLexerMapBackup = 0;
    }
}

QWidget* EditorLexerManager::getLexerManagerWidget(QWidget *parent)
{
    return new EditorLexerManagerWidget(mLexerMap, parent);
}



QList<QString> EditorLexerManager::getLexerNames()
{
    QList<QString> lexNames;
    foreach(const QString &name, mLexerMap->keys()) {
        if(mLexerMap->value(name)->isAvailable)
            lexNames.append(name);
    }

    return lexNames;
}



void EditorLexerManager::initializeLexers()
{
    EditorLexerCfg *eLexer;

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexerstest");
    QsciLexer *lex = new QsciLexerPython();
    lex->readSettings(qset);
    lex->writeSettings(qset);

    eLexer = new EditorLexerCfg(&createLexPython, &saveLexPython, &copyLexPython, true);
    mLexerMap->insert("Normal Text", eLexer);

    eLexer = new EditorLexerCfg(&createLexCPP, &saveLexCPP, &copyLexCPP);
    mLexerMap->insert("C++", eLexer);

    eLexer = new EditorLexerCfg(&createLexJava, &saveLexJava, &copyLexJava);
    mLexerMap->insert("Java", eLexer);

    eLexer = new EditorLexerCfg(&createLexPython, &saveLexPython, &copyLexPython);
    mLexerMap->insert("Python", eLexer);

    restoreBasicConfig();
}

