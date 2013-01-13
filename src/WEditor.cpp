
#include "Logger.h"
#include "WEditor.h"
#include "WEditorBinder.h"

using namespace Wolverine;




Editor::Editor(QWidget *parent) :
    QsciScintilla(parent),
    mBinder(0)
{
    initialize();
}


Editor::Editor(EditorBinder *doc, QWidget *parent) :
    QsciScintilla(parent),
    mBinder(doc)
{
    initialize();
}


Editor::~Editor()
{

}


void Editor::initialize()
{
    this->setFocusPolicy(Qt::ClickFocus);
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


/**
 *  focusInEvent() handler
 *
 */
//virtual
void Editor::focusInEvent(QFocusEvent *event)
{
    emit focusReceived();
    QsciScintilla::focusInEvent(event);
}
