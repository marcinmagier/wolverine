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
 *  @file       WEditorBinder.cpp
 *  @brief      Wolverine::EditorBinder class implementation.
 */




#include "WEditorBinder.h"
#include "WEditor.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"

#include "Logger.h"


#include <QFile>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QTextStream>
#include <QTextCodec>

#include <QDebug>


using namespace Wolverine;


int EditorBinder::sNewFileNo = 1;


EditorBinder::EditorBinder() :
    QObject(),
    QFileInfo( QString(tr("New %1").arg(sNewFileNo++)) )
{
    mCodec = QTextCodec::codecForLocale();
    AppSettings::instance()->scintilla->addCodecAvailable(mCodec->name());
    mEditors.clear();
    mStatusInt = Modified;
    mStatusExt = NotExists;
    mWatcher = new QFileSystemWatcher();
    connect( mWatcher, SIGNAL(fileChanged(QString)),
                 this, SLOT(onFileChanged(QString)) );
}


EditorBinder::EditorBinder(const QString &path) :
    QObject(),
    QFileInfo(path)
{
    mCodec = QTextCodec::codecForLocale();
    mEditors.clear();

    if(exists()) {
        QString fileName(this->canonicalFilePath());
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
            LOG_ERROR("Cannot open the file %s", fileName.constData());

        mCodec = QTextCodec::codecForUtfText(file.readLine(16), mCodec);
        file.close();
    }

    AppSettings::instance()->scintilla->addCodecAvailable(mCodec->name());

    if(!exists()) {
        mStatusInt = Modified;
        mStatusExt = NotExists;
    } else if(!isWritable()) {
        mStatusInt = Unmodified;
        mStatusExt = ReadOnly;
    } else {
        mStatusInt = Unmodified;
        mStatusExt = Normal;
    }

    mWatcher = new QFileSystemWatcher();
    mWatcher->addPath(canonicalFilePath());
    connect( mWatcher, SIGNAL(fileChanged(QString)),
                 this, SLOT(onFileChanged(QString)) );

}


EditorBinder::~EditorBinder()
{
    foreach(Editor *editor, mEditors) {
        delete editor;
    }

    delete mWatcher;
}



bool EditorBinder::hasEditors() const
{
    return !mEditors.empty();
}


Editor* EditorBinder::getEditor()
{
    if(mEditors.empty())
        return getNewEditor();

    return mEditors[0];
}

EditorList& EditorBinder::getEditors()
{
   return mEditors;
}


Editor* EditorBinder::getNewEditor()
{
    Editor *newEditor = new Editor(this);
    mEditors.append(newEditor);
    connect( newEditor, SIGNAL(modificationChanged(bool)),
                  this, SLOT(onEditorModificationChanged(bool)) );

    loadFile();

    return newEditor;
}


Editor* EditorBinder::getLinkedEditor(Editor *editor)
{
    Editor *newEditor = new Editor(this);
    mEditors.append(newEditor);
    newEditor->setDocument(editor->document());
    newEditor->setLexer(editor->getLexerName());
    connect( newEditor, SIGNAL(modificationChanged(bool)),
                  this, SLOT(onEditorModificationChanged(bool)) );
    return newEditor;
}


void EditorBinder::removeEditor(Editor *editor)
{
    QString lexName = editor->getLexerName();
    mEditors.removeAll(editor);
    delete editor;
    foreach(Editor *editor, mEditors) {
        editor->setLexer(lexName);
    }
}



QString EditorBinder::getCodecName()
{
    return QString(mCodec->name());
}

void EditorBinder::setCodecName(const QString &name, bool reload)
{
    QTextCodec *tmp = QTextCodec::codecForName(name.toAscii());
    if(tmp)
        mCodec = tmp;
    else
        LOG_WARNING("Codec %s not known", name.constData());

    if(reload)
        loadFile();
}



void EditorBinder::onEditorModificationChanged(bool modified)
{
    StatusInt stat = modified ? Modified : Unmodified;
    setStatusInt(stat);
}


void EditorBinder::onFileChanged(const QString &)
{
    QFileInfo::refresh();

    if(!exists()) {
        setStatusExt(NotExists);
        mStatusInt = Modified;
    } else if(!isWritable()) {
        setStatusExt(ReadOnly);
        mStatusInt = Unmodified;
    } else {
        setStatusExt(Normal, true);
    }
}


EditorBinder::StatusInt EditorBinder::getStatusInt() const
{
    return mStatusInt;
}

EditorBinder::StatusExt EditorBinder::getStatusExt() const
{
    return mStatusExt;
}

void EditorBinder::setStatusInt(EditorBinder::StatusInt stat, bool force)
{
    if(mStatusExt == ReadOnly)
        return;

    if( (mStatusInt != stat) || force) {
        emit statusIntChanged(static_cast<int>(stat));
        mStatusInt = stat;
    }
}

void EditorBinder::setStatusExt(StatusExt stat, bool force)
{
    if( (mStatusExt != stat) || force) {
        emit statusExtChanged(static_cast<int>(stat));
        mStatusExt = stat;
    }
}

void EditorBinder::loadFile()
{
    if(mEditors.length() == 0)
        LOG_WARNING("Editor doesn't exist");

    if(exists()) {
        QString fileName(this->canonicalFilePath());
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
            LOG_ERROR("Cannot open the file %s", fileName.constData());

        QTextStream in(&file);
        in.setCodec(mCodec);
        mEditors[0]->setText(in.readAll());
        file.close();

        setStatusInt(Unmodified);
    }
}

