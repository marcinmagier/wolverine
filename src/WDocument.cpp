
#include "WDocument.h"
#include "WEditor.h"

#include <QFileInfo>

using namespace Wolverine;


int Document::sNewFileNo = 1;


Document::Document()
{
    mFile = QFileInfo( QString(tr("New %1").arg(sNewFileNo)) );
    sNewFileNo++;
    mEditors.clear();
}


Document::Document(const QString &path)
{
    mFile = QFileInfo(path);
    mEditors.clear();
}


Document::~Document()
{
    foreach(Editor *editor, mEditors) {
        delete editor;
    }
}


QString Document::getFileName() const
{
    return mFile.fileName();
}


QString Document::getAbsoluteFilePath() const
{
    return mFile.absoluteFilePath();
}


bool Document::exists() const
{
    return mFile.exists();
}


bool Document::isWritable() const
{
    return mFile.isWritable();
}


bool Document::hasEditors() const
{
    return !mEditors.empty();
}


Editor* Document::getEditor()
{
    if(mEditors.empty())
        return 0;

    return mEditors[0];
}


Editor* Document::getNewEditor()
{
    Editor *newEditor = new Editor();
    mEditors.append(newEditor);
    return newEditor;
}
