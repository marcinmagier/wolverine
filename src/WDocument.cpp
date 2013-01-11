
#include "WDocument.h"
#include "WEditor.h"

#include <QFileInfo>

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
    return newEditor;
}


Editor* EditorBinder::getLinkedEditor(Editor *editor)
{
    Editor *newEditor = new Editor();
    mEditors.append(newEditor);
    newEditor->setDocument(editor->document());
    return newEditor;
}


void EditorBinder::removeEditor(Editor *editor)
{
    mEditors.removeAll(editor);
    delete editor;
}


QIcon EditorBinder::getIcon() const
{
    if(!exists())
        return QIcon(":/save_red.png");

    if(!isWritable())
        return QIcon(":/save_grey.png");

    return QIcon(":/save_blue.png");
}
