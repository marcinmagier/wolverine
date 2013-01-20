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

#include "Qsci/qscilexer.h"

#include <QWidget>
#include <QStringList>
#include <QAction>
#include <QApplication>
#include <QSettings>



namespace Wolverine
{

class EditorLexer
{
public:

    explicit EditorLexer(bool available = false) : mLexer(0), mAvailable(available) {}
    ~EditorLexer() { delete mLexer; }

    void setAvailable(bool val) { mAvailable = val; }
    bool isAvailable() { return mAvailable; }

    void setLexer(QsciLexer *lexer) { mLexer = lexer; }
    QsciLexer* getLexer() { return mLexer; }


private:
    QsciLexer *mLexer;
    bool mAvailable;
};

}



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
    initializeLexers();
}

EditorLexerManager::~EditorLexerManager()
{
    saveConfig();

    foreach(EditorLexer *eLexer, mLexerMap) {
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






void EditorLexerManager::initializeLexers()
{
    EditorLexer *eLexer;

    eLexer = new EditorLexer();
    mLexerMap["Normal Text"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["Bash"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["Batch"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["C++"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["C#"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["HTML"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["Java"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["Makefile"] = eLexer;

    eLexer = new EditorLexer();
    mLexerMap["Python"] = eLexer;

    restoreBasicConfig();
}



void EditorLexerManager::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");

    if(!qset.isWritable())
        return;

    foreach(QString lexName, mLexerMap.keys()) {
        qset.beginGroup(lexName);
        EditorLexer *eLexer = mLexerMap[lexName];
        qset.setValue("available", QVariant::fromValue( eLexer->isAvailable()) );
        qset.endGroup();
    }
}


void EditorLexerManager::restoreBasicConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");

    foreach(QString lexName, mLexerMap.keys()) {
        qset.beginGroup(lexName);
        EditorLexer *eLexer = mLexerMap[lexName];
        eLexer->setAvailable( qset.value("available").toBool() );
        qset.endGroup();
    }
}


void EditorLexerManager::restoreLexerConfig(const QString &lexerName)
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");
    qset.beginGroup(lexerName);

    qset.endGroup();
}

