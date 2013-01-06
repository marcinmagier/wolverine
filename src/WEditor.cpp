
#include "WEditor.h"
#include "WDocument.h"

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QsciScintilla(parent),
    mDocument(0)
{

}


Editor::Editor(Document *document, QWidget *parent) :
    QsciScintilla(parent),
    mDocument(document)
{

}



Editor::~Editor()
{

}
