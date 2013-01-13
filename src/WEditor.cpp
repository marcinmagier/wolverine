
#include "Logger.h"
#include "WEditor.h"
#include "WEditorBinder.h"

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QsciScintilla(parent),
    mBinder(0)
{

}


Editor::Editor(EditorBinder *doc, QWidget *parent) :
    QsciScintilla(parent),
    mBinder(doc)
{

}



Editor::~Editor()
{

}


Editor* Editor::getLinkedCopy()
{
   return mBinder->getLinkedEditor(this);
}


void Editor::setBinder(EditorBinder *doc)
{
    mBinder = doc;
}


EditorBinder* Editor::getBinder()
{
    if(mBinder == 0)
        LOG_ERROR("There is no binder asociated with the editor");

    return mBinder;
}
