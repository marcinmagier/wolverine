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
 *  @file       WPanelSplitter.cpp
 *  @brief      Wolverine::PanelSplitter class implementation.
 */

#include "WPanelSplitter.h"
#include "WEditor.h"
#include "WEditorBinder.h"


using namespace Wolverine;


/**
 *  Constructor.
 *
 * @param parent
 */
PanelSplitter::PanelSplitter(QWidget *parent) :
    QSplitter(parent)
{
    this->setOrientation(Qt::Vertical);

    connect( this, SIGNAL(splitterMoved(int,int)),
             this, SLOT(onSplitterMoved(int,int)) );
}


/**
 *  Destructor.
 */
PanelSplitter::~PanelSplitter()
{
    int i=0;
    while(i < this->count()) {
        if(mCurrentEditor != this->widget(i))
            this->removeEditor(i);
        else
            i++;
    }
    mCurrentEditor->setParent(0);   // Do not delete editor
    disconnect( mCurrentEditor, SIGNAL(focusReceived()),
                          this, SLOT(onInternalWidgetFocusReceived()) );

}


/**
 *  Adds widget to the splitter.
 *
 * @param editor
 */
void PanelSplitter::addWidget(Editor *editor)
{
    mCurrentEditor = editor;
    connect( editor, SIGNAL(focusReceived()),
               this, SLOT(onInternalWidgetFocusReceived()) );

    QSplitter::addWidget(editor);
}


/**
 *  Returns current editor.
 *
 * @return
 */
Editor* PanelSplitter::getEditor()
{
    return mCurrentEditor;
}


/**
 *  Checks if splitter has given editor.
 *
 * @param editor
 * @return
 */
bool PanelSplitter::hasEditor(Editor *editor)
{
    for(int i=0; i<count(); i++) {
        Editor *tmpEditor = dynamic_cast<Editor*>(this->widget(i));
        if(tmpEditor->getBinder() == editor->getBinder())
            return true;
    }
    return false;
}


/**
 *  Checks if splitter has editor associated with given file path.
 *
 * @param filePath
 * @return
 */
bool PanelSplitter::hasEditor(const QString &filePath)
{
    for(int i=0; i<count(); i++) {
        Editor *tmpEditor = dynamic_cast<Editor*>(this->widget(i));
        if(tmpEditor->getBinder()->absoluteFilePath() == filePath)
            return true;
    }
    return false;
}


/**
 *  Removes editor from splitter.
 *
 * @param idx
 */
void PanelSplitter::removeEditor(int idx)
{
    Editor *editor = dynamic_cast<Editor*>(this->widget(idx));
    EditorBinder *binder = editor->getBinder();
    binder->removeEditor(editor);
}


/**
 *  Splits current editor into linked editors.
 */
void PanelSplitter::split()
{
    Editor *newEditor = mCurrentEditor->getLinkedCopy();
    this->addWidget(newEditor);
}


/**
 *  Editor's focusReceived() handler.
 */
void PanelSplitter::onInternalWidgetFocusReceived()
{
    mCurrentEditor = dynamic_cast<Editor*>(this->sender());
    emit focusReceived();
}


/**
 *  Checks if editor should be closed.
 */
void PanelSplitter::onSplitterMoved(int /*pos*/, int /*index*/)
{
    QList<int> sizes = this->sizes();

    int i=0;
    while(i < this->count()) {
        if(sizes[i] == 0) {
            this->removeEditor(i);
            sizes.removeAt(i);
        }
        else {
            i++;
        }
    }

    mCurrentEditor = dynamic_cast<Editor*>(this->widget(0));
    mCurrentEditor->setFocus();
}
