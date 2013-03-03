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
#include <QFile>
#include <QFileInfo>
#include <QRegExp>


#include <QDebug>



#define LEX_INI_FILE "lexers"


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

    QString fileName = fileInfo->fileName();
    foreach(const QString &lexName, mLexerMap->keys()) {
        EditorLexerCfg *eLexer = mLexerMap->value(lexName);
        foreach(const QString &fileNamePattern, eLexer->fileNamesPatterns) {
            QRegExp re(fileNamePattern);
            re.setPatternSyntax(QRegExp::Wildcard);
            re.setCaseSensitivity(Qt::CaseInsensitive);
            if( re.exactMatch(fileName))
                return lexName;
        }
    }

    QFile file(fileInfo->canonicalFilePath());
    if( file.open(QIODevice::ReadOnly) ) {
        QString firstTextLine;
        while(!file.atEnd() && firstTextLine.isEmpty())
            firstTextLine = QString::fromLatin1(file.readLine().constData()).simplified();

        if(!file.atEnd()) {
            foreach(const QString &lexName, mLexerMap->keys()) {
                EditorLexerCfg *eLexer = mLexerMap->value(lexName);
                foreach(const QString &fileFirstLinePattern, eLexer->fileFirstLinePatterns) {
                    QRegExp re(fileFirstLinePattern);
                    re.setPatternSyntax(QRegExp::Wildcard);
                    re.setCaseSensitivity(Qt::CaseInsensitive);
                    if( re.exactMatch(firstTextLine))
                        return lexName;
                }
            }
        }
        file.close();
    }

    return QString("Normal Text");
}


QsciLexer* EditorLexerManager::getLexer(const QString &lexName)
{
    if(!mLexerMap->contains(lexName))
        LOG_ERROR("Lexer not known!");

    EditorLexerCfg *eLexer = mLexerMap->value(lexName);
    if(eLexer->lexer)
        return eLexer->lexer;

    eLexer->createFunction(eLexer);
    eLexer->isAvailable = true;
    loadConfig(lexName, eLexer);
    return eLexer->lexer;
}




void EditorLexerManager::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), LEX_INI_FILE);

    if(!qset.isWritable())
        return;

    foreach(const QString &lexName, mLexerMap->keys()) {
        EditorLexerCfg *eLexer = mLexerMap->value(lexName);
        qset.beginGroup(lexName);
        qset.setValue( "available", QVariant(eLexer->isAvailable) );
        qset.setValue("file_name_patterns", QVariant(eLexer->fileNamesPatterns) );
        qset.setValue("file_first_line_patterns", QVariant(eLexer->fileFirstLinePatterns) );
        if(eLexer->lexer)
            eLexer->lexer->writeSettings(qset);
        qset.endGroup();
    }
}


void EditorLexerManager::loadConfig(const QString &lexName, EditorLexerCfg *eLexer)
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), LEX_INI_FILE);
    qset.beginGroup(lexName);
    eLexer->lexer->readSettings(qset);
    qset.endGroup();
}

void EditorLexerManager::restoreBasicConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), LEX_INI_FILE);

    foreach(const QString &lexName, mLexerMap->keys()) {
        qset.beginGroup(lexName);
        EditorLexerCfg *eLexer = mLexerMap->value(lexName);
        if(qset.contains("available"))
            eLexer->isAvailable = qset.value("available").toBool();
        if(qset.contains("file_name_patterns"))
            eLexer->fileNamesPatterns = qset.value("file_name_patterns").toStringList();
        if(qset.contains("file_first_line_patterns"))
            eLexer->fileFirstLinePatterns = qset.value("file_first_line_patterns").toStringList();
        qset.endGroup();
    }
}




void EditorLexerManager::createConfigurationBackup()
{
    dropConfigurationBackup();
    mLexerMapBackup = new EditorLexerCfgMap();
    foreach(const QString &lexName, mLexerMap->keys()) {
        //this->getLexer(lexName);    //We have to create all lexers to have backup
        EditorLexerCfg *origin = mLexerMap->value(lexName);
        EditorLexerCfg *backup = new EditorLexerCfg(origin->createFunction, origin->isAvailable);
        backup->createFunction(backup);
        backup->lexer->copyFrom(origin->lexer);
        backup->fileNamesPatterns = origin->fileNamesPatterns;
        backup->fileFirstLinePatterns = origin->fileFirstLinePatterns;
        mLexerMapBackup->insert(lexName, backup);
    }
}

void EditorLexerManager::restoreConfigurationBackup()
{
    foreach(const QString &lexName, mLexerMap->keys()) {
        EditorLexerCfg *origin = mLexerMap->value(lexName);
        EditorLexerCfg *backup = mLexerMapBackup->value(lexName);
        origin->isAvailable = backup->isAvailable;
        origin->fileNamesPatterns = backup->fileNamesPatterns;
        origin->fileFirstLinePatterns = backup->fileFirstLinePatterns;
        origin->lexer->copyFrom(backup->lexer);
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
    foreach(const QString &lexName, mLexerMap->keys()) {
        this->getLexer(lexName);    //We have to create all lexers
    }
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

    eLexer = new EditorLexerCfg(&createLexNormalText, true);
    eLexer->fileNamesPatterns << "*.txt";
    mLexerMap->insert("Normal Text", eLexer);

    eLexer = new EditorLexerCfg(&createLexBash);
    eLexer->fileNamesPatterns << "*.sh" << "*.run";
    eLexer->fileFirstLinePatterns << "*bash*" << "*/sh*";
    mLexerMap->insert("Bash", eLexer);

    eLexer = new EditorLexerCfg(&createLexCPP);
    eLexer->fileNamesPatterns << "*.c" << "*.cc" << "*.cpp" << "*.cxx" << "*.c++"
                              << "*.h" << "*.hh" << "*.hpp" << "*.hxx";
    mLexerMap->insert("C++", eLexer);

    eLexer = new EditorLexerCfg(&createLexHTML);
    eLexer->fileNamesPatterns << "*.htm*" << "*.[xd]htm*";
    eLexer->fileFirstLinePatterns << "*html*";
    mLexerMap->insert("HTML", eLexer);

    eLexer = new EditorLexerCfg(&createLexJava);
    eLexer->fileNamesPatterns << "*.java";
    mLexerMap->insert("Java", eLexer);

    eLexer = new EditorLexerCfg(&createLexPython);
    eLexer->fileNamesPatterns << "*.py";
    eLexer->fileFirstLinePatterns << "*python*";
    mLexerMap->insert("Python", eLexer);

    restoreBasicConfig();
}

