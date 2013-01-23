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

#include "Logger.h"


#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextCodec>

#include <QDebug>


using namespace Wolverine;


int EditorBinder::sNewFileNo = 1;


EditorBinder::EditorBinder() :
    QObject(),
    QFileInfo( QString(tr("New %1").arg(sNewFileNo++)) )
{
    mEditors.clear();
}


EditorBinder::EditorBinder(const QString &path) :
    QObject(),
    QFileInfo(path)
{
    mEditors.clear();
}


EditorBinder::~EditorBinder()
{
    foreach(Editor *editor, mEditors) {
        delete editor;
    }
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

    if(exists()) {
        QString fileName(this->canonicalFilePath());
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
            LOG_ERROR("Cannot open the file %s", fileName.constData());

        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForLocale());
        newEditor->setText(in.readAll());
    }
    return newEditor;
}


Editor* EditorBinder::getLinkedEditor(Editor *editor)
{
    Editor *newEditor = new Editor(this);
    mEditors.append(newEditor);
    newEditor->setDocument(editor->document());
    newEditor->setLexer(editor->getLexerName());
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


QIcon EditorBinder::getIcon() const
{
    if(!exists())
        return QIcon(":/save_red.png");

    if(!isWritable())
        return QIcon(":/save_grey.png");

    return QIcon(":/save_blue.png");
}
