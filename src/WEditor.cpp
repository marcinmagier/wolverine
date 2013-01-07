
#include "WEditor.h"
#include "WDocument.h"

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QsciScintilla(parent),
    mDocument(0)
{

}


Editor::Editor(Document *doc, QWidget *parent) :
    QsciScintilla(parent),
    mDocument(doc)
{

}



Editor::~Editor()
{

}


void Editor::setDocument(Document *doc)
{
    mDocument = doc;
}


Document* Editor::getDocument()
{
    return mDocument;
}
