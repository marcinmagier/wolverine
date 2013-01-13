
#include "WEditorProxy.h"


using namespace Wolverine;


EditorProxy::EditorProxy()
{

}

EditorProxy::~EditorProxy()
{

}


Editor *EditorProxy::getCurrentEditor()
{
    return mCurrentEditor;
}

void EditorProxy::setCurrentEditor(Editor *editor)
{
    if(mCurrentEditor != editor) {
        mCurrentEditor = editor;
        emit currentEditorChanged(mCurrentEditor);
    }
}
