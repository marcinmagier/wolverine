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
 *  @file       WPanelTabContent.cpp
 *  @brief      Wolverine::PanelTabContent class implementation.
 */


#include "WPanelTabContent.h"
#include "WEditor.h"
#include "WEditorBinder.h"


using namespace Wolverine;




/**
 *  Constructor.
 *
 * @param parent
 */
PanelTabContent::PanelTabContent(QWidget *parent) :
    QSplitter(parent)
{
    this->setOrientation(Qt::Vertical);

    connect( this, SIGNAL(splitterMoved(int,int)),
             this, SLOT(onSplitterMoved(int,int)) );
}


/**
 *  Destructor.
 */
PanelTabContent::~PanelTabContent()
{
    int i=0;
    while(i < count()) {
        if(mEditorProxy != this->widget(i))
            this->removeEditor(i);
        else
            i++;
    }
    mEditorProxy->setParent(0);   // Do not delete editor
    disconnect( mEditorProxy, SIGNAL(focusReceived()),
                        this, SLOT(onInternalWidgetFocusReceived()) );

}


/**
 *  Adds widget to the splitter.
 *
 * @param editor
 */
void PanelTabContent::addWidget(Editor *editor)
{
    mEditorProxy = editor;
    connect( mEditorProxy, SIGNAL(focusReceived()),
                     this, SLOT(onInternalWidgetFocusReceived()), Qt::UniqueConnection );

    QSplitter::addWidget(mEditorProxy);
}


/**
 *  Returns current editor.
 *
 * @return
 */
Editor* PanelTabContent::getEditor()
{
    return mEditorProxy;
}


/**
 *  Checks if splitter has given editor.
 *
 * @param editor
 * @return
 */
bool PanelTabContent::hasEditor(Editor *editor)
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
bool PanelTabContent::hasEditor(const QString &filePath)
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
void PanelTabContent::removeEditor(int index)
{
    Editor *editor = dynamic_cast<Editor*>(this->widget(index));
    Editor::removeEditor(editor);
}


/**
 *  Splits current editor into linked editors.
 */
void PanelTabContent::split()
{
    Editor *newEditor = mEditorProxy->getLinkedCopy();
    this->addWidget(newEditor);
}


/**
 *  Editor's focusReceived() handler.
 */
void PanelTabContent::onInternalWidgetFocusReceived()
{
    mEditorProxy = dynamic_cast<Editor*>(this->sender());
    emit focusReceived();
}


/**
 *  Checks if editor should be closed.
 *
 * BUG Qt 4.8.1 Windows
 * Feature doesn't work fine because there is a problem with widgets within QSplitter. Widgets are added
 * in reversed order (???) so that sizes[i] != widget(i).
 */
void PanelTabContent::onSplitterMoved(int /*pos*/, int /*index*/)
{
    QList<int> sizes = this->sizes();

    int i=0;
    while(i < count()) {
        if(sizes[i] == 0) {
            this->removeEditor(i);
            sizes.removeAt(i);
        }
        else {
            i++;
        }
    }

    mEditorProxy = dynamic_cast<Editor*>(this->widget(0));
    mEditorProxy->setFocus();
}
