
#include "WDocument.h"
#include "WEditor.h"

#include <QFileInfo>

using namespace Wolverine;


int Document::sNewFileNo = 1;


Document::Document() :
    QObject(),
    QFileInfo( QString(tr("New %1").arg(sNewFileNo++)) )
{
    mEditors.clear();
}


Document::Document(const QString &path) :
    QObject(),
    QFileInfo(path)
{
    mEditors.clear();
}


Document::~Document()
{
    foreach(Editor *editor, mEditors) {
        delete editor;
    }
}



bool Document::hasEditors() const
{
    return !mEditors.empty();
}


Editor* Document::getEditor()
{
    if(mEditors.empty())
        return getNewEditor();

    return mEditors[0];
}

EditorList& Document::getEditors()
{
   return mEditors;
}


Editor* Document::getNewEditor()
{
    Editor *newEditor = new Editor(this);
    mEditors.append(newEditor);
    return newEditor;
}


QIcon Document::getIcon() const
{
    if(!exists())
        return QIcon(":/save_red.png");

    if(!isWritable())
        return QIcon(":/save_grey.png");

    return QIcon(":/save_blue.png");
}
