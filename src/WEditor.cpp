
#include "Logger.h"
#include "WEditor.h"
#include "WEditorBinder.h"

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QsciScintilla(parent),
    mDocument(0)
{

}


Editor::Editor(EditorBinder *doc, QWidget *parent) :
    QsciScintilla(parent),
    mDocument(doc)
{

}



Editor::~Editor()
{

}


Editor* Editor::getLinkedCopy()
{
   return mDocument->getLinkedEditor(this);
}

void Editor::setBinder(EditorBinder *doc)
{
    mDocument = doc;
}


EditorBinder* Editor::getBinder()
{
    if(mDocument == 0)
        LOG_ERROR("There is no document asociated with the editor");

    return mDocument;
}
