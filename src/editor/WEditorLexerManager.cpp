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


namespace Wolverine
{

typedef QsciLexer* (EditorLexerManager::*pfCreateLexerFunct)(const QString&, QSettings*);
typedef void (EditorLexerManager::*pfSaveLexerFunct)(QsciLexer*, const QString&, QSettings*);


class EditorLexer
{
public:

    explicit EditorLexer(pfCreateLexerFunct createFunct, pfSaveLexerFunct saveFunct, bool available = false) :
        mLexer(0), mCreateFunction(createFunct), mSaveFunction(saveFunct), mAvailable(available) {}
    ~EditorLexer() { delete mLexer; }

    void setAvailable(bool val) { mAvailable = val; }
    bool isAvailable() { return mAvailable; }

    void setLexer(QsciLexer *lexer) { mLexer = lexer; }
    QsciLexer* getLexer() { return mLexer; }

    pfCreateLexerFunct getCreateFunct() { return mCreateFunction; }
    pfSaveLexerFunct getSaveFunct() { return mSaveFunction;}

private:
    QsciLexer *mLexer;
    pfCreateLexerFunct mCreateFunction;
    pfSaveLexerFunct mSaveFunction;
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



QString EditorLexerManager::getLexerName(QFileInfo *fileInfo)
{
    if(!fileInfo->exists())
        return QString("Normal Text");

    return QString("C++");
}


QsciLexer* EditorLexerManager::getLexer(const QString &lexName)
{
    if(!mLexerMap.contains(lexName))
        LOG_ERROR("Lexer not known!");

    EditorLexer *eLexer = mLexerMap[lexName];
    QsciLexer *lexer = eLexer->getLexer();
    if(lexer)
        return lexer;

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");
    pfCreateLexerFunct createFunct= eLexer->getCreateFunct();
    lexer = (this->*createFunct)(lexName, &qset);
    eLexer->setLexer(lexer);

    return lexer;
}




void EditorLexerManager::saveConfig()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "lexers");

    if(!qset.isWritable())
        return;

    foreach(QString lexName, mLexerMap.keys()) {
        qset.beginGroup(lexName);
        EditorLexer *eLexer = mLexerMap[lexName];
        qset.setValue( "available", QVariant::fromValue( eLexer->isAvailable()) );
        QsciLexer *lexer = eLexer->getLexer();
        if(lexer) {
            qset.setValue( "def_font", QVariant::fromValue(lexer->defaultFont()) );
            qset.setValue( "def_fgcolor", QVariant::fromValue(lexer->defaultColor()) );
            qset.setValue( "def_bgcolor", QVariant::fromValue(lexer->defaultPaper()) );

            pfSaveLexerFunct saveFunct= eLexer->getSaveFunct();
            (this->*saveFunct)(lexer, lexName, &qset);
        }
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

    eLexer = new EditorLexer(&EditorLexerManager::createLexerPython, &EditorLexerManager::saveLexerPython);
    mLexerMap["Normal Text"] = eLexer;

    eLexer = new EditorLexer(&EditorLexerManager::createLexerCPP, &EditorLexerManager::saveLexerCPP);
    mLexerMap["C++"] = eLexer;

    eLexer = new EditorLexer(0, 0);
    mLexerMap["Java"] = eLexer;

    eLexer = new EditorLexer(&EditorLexerManager::createLexerPython, &EditorLexerManager::saveLexerPython);
    mLexerMap["Python"] = eLexer;

    restoreBasicConfig();
}


QsciLexer* EditorLexerManager::createLexerCPP(const QString &name, QSettings *qset)
{
    return new QsciLexerCPP();
}

void EditorLexerManager::saveLexerCPP(QsciLexer *lexer, const QString &name, QSettings *qset)
{
    qset->beginGroup(name);
    qset->setValue("font", QVariant::fromValue(lexer->font(0)));
    qset->endGroup();
}

QsciLexer* EditorLexerManager::createLexerPython(const QString &name, QSettings *qset)
{
    return new QsciLexerPython();
}

void EditorLexerManager::saveLexerPython(QsciLexer *lexer, const QString &name, QSettings *qset)
{
    //QsciLexerPython *lexerPython = dynamic_cast<QsciLexerPython*>(lexer);
    qDebug() << lexer->description(QsciLexerPython::Default);
    qset->beginGroup(lexer->description(QsciLexerPython::Default));
    qset->setValue( "font", QVariant::fromValue(lexer->font(QsciLexerPython::Default)) );
    qset->setValue( "fgcolor", QVariant::fromValue(lexer->color(QsciLexerPython::Default)) );
    qset->setValue( "bgcolor", QVariant::fromValue(lexer->paper(QsciLexerPython::Default)) );
    qset->setValue( "filleol", QVariant::fromValue(lexer->defaultEolFill(QsciLexerPython::Default)) );
    qset->endGroup();

    qDebug() << lexer->description(QsciLexerPython::Comment);
    qset->beginGroup(lexer->description(QsciLexerPython::Comment));
    qset->setValue( "font", QVariant::fromValue(lexer->font(QsciLexerPython::Comment)) );
    qset->setValue( "fgcolor", QVariant::fromValue(lexer->color(QsciLexerPython::Comment)) );
    qset->setValue( "bgcolor", QVariant::fromValue(lexer->paper(QsciLexerPython::Comment)) );
    qset->setValue( "filleol", QVariant::fromValue(lexer->defaultEolFill(QsciLexerPython::Comment)) );
    qset->endGroup();

    qDebug() << lexer->description(QsciLexerPython::Number);
    qset->beginGroup(lexer->description(QsciLexerPython::Number));
    qset->setValue( "font", QVariant::fromValue(lexer->font(QsciLexerPython::Number)) );
    qset->setValue( "fgcolor", QVariant::fromValue(lexer->color(QsciLexerPython::Number)) );
    qset->setValue( "bgcolor", QVariant::fromValue(lexer->paper(QsciLexerPython::Number)) );
    qset->setValue( "filleol", QVariant::fromValue(lexer->defaultEolFill(QsciLexerPython::Number)) );
    qset->endGroup();
}


