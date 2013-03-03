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
 *  @file       WEditorBinder.cpp
 *  @brief      Wolverine::EditorBinder class implementation.
 */




#include "WEditorBinder.h"
#include "WEditor.h"
#include "WEditorLexerManager.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"
#include "CfgScintillaSettings.h"

#include "Logger.h"


#include <QFile>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QDir>
#include <QTextStream>
#include <QTextCodec>

#include <QDebug>


using namespace Wolverine;


int EditorBinder::sNewFileNo = 1;


/**
 *  Constructor.
 */
EditorBinder::EditorBinder() :
    QObject(),
    QFileInfo( QString(tr("New %1").arg(sNewFileNo++)) )
{
    mCodec = QTextCodec::codecForLocale();
    AppSettings::instance()->scintilla->addCodecAvailable(mCodec->name());
    mEditors.clear();

    mStatusInt = Modified;
    mStatusExt = New;
    mWatcher = new QFileSystemWatcher();
    connect( mWatcher, SIGNAL(fileChanged(QString)),
                 this, SLOT(onFileChanged(QString)) );

    mLexerManager = EditorLexerManager::instance();
    mLexerName = mLexerManager->getLexerName(this);

    mEolMode = guessEol();
}


/**
 *  Constructor.
 *
 * @param path
 */
EditorBinder::EditorBinder(const QString &path) :
    QObject(),
    QFileInfo(path)
{
    mCodec = QTextCodec::codecForLocale();
    mEditors.clear();

    if(exists()) {
        QString fileName(this->canonicalFilePath());
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
            LOG_ERROR("Cannot open the file %s", fileName.constData());

        #define MAX_CHARS_READ 16
        mCodec = QTextCodec::codecForUtfText(file.readLine(MAX_CHARS_READ), mCodec);
        file.close();
    }

    AppSettings::instance()->scintilla->addCodecAvailable(mCodec->name());

    if(!exists()) {
        mStatusInt = Modified;
        mStatusExt = NotExists;
    } else if(!isWritable()) {
        mStatusInt = Unmodified;
        mStatusExt = ReadOnly;
    } else {
        mStatusInt = Unmodified;
        mStatusExt = Normal;
    }

    mWatcher = new QFileSystemWatcher();
    connect( mWatcher, SIGNAL(fileChanged(QString)),
                 this, SLOT(onFileChanged(QString)) );

    if(exists())
        mWatcher->addPath(absoluteFilePath());

    mLexerManager = EditorLexerManager::instance();
    mLexerName = mLexerManager->getLexerName(this);

    mEolMode = guessEol();
}


/**
 *  Destructor.
 */
EditorBinder::~EditorBinder()
{
    foreach(Editor *editor, mEditors) {
        delete editor;
    }

    delete mWatcher;
}


/**
 *  Checks if has any editor.
 *
 * @return
 */
bool EditorBinder::hasEditors() const
{
    return !mEditors.empty();
}


/**
 *  Returns editor. New editor is created if there is no editors.
 *
 * @return
 */
Editor* EditorBinder::getEditor()
{
    if(mEditors.empty())
        return getNewEditor();

    return mEditors[0];
}


/**
 *  Returns list of editors associated with binder.
 *
 * @return
 */
EditorList& EditorBinder::getEditors()
{
   return mEditors;
}


/**
 *  Creates and returns new editor.
 *
 * @return
 */
Editor* EditorBinder::getNewEditor()
{
    Editor *newEditor = new Editor(this);
    newEditor->setLexer(mLexerManager->getLexer(mLexerName));
    newEditor->setEolMode(mEolMode);
    mEditors.append(newEditor);
    connect( newEditor, SIGNAL(modificationChanged(bool)),
                  this, SLOT(onEditorModificationChanged(bool)) );

    loadFile();

    return newEditor;
}


/**
 *  Creates and returns linked editor.
 *
 * Linked editors share the same qsci document.
 *
 * @param editor
 * @return
 */
Editor* EditorBinder::getLinkedEditor(Editor *editor)
{
    Editor *newEditor = new Editor(this);
    mEditors.append(newEditor);
    newEditor->setDocument(editor->document());
    newEditor->setLexer(mLexerManager->getLexer(mLexerName));
    newEditor->setEolMode(mEolMode);
    connect( newEditor, SIGNAL(modificationChanged(bool)),
                  this, SLOT(onEditorModificationChanged(bool)) );
    return newEditor;
}


/**
 *  Removes editor.
 *
 * @param editor
 */
void EditorBinder::removeEditor(Editor *editor)
{
    mEditors.removeAll(editor);
    delete editor;

    // Update lexer for linked editors.
    setLexer(mLexerManager->getLexerName(this));
}



/**
 *  Returns current codec name.
 *
 * @return
 */
QString EditorBinder::getCodecName()
{
    return QString(mCodec->name());
}


/**
 *  Update codec.
 *
 * @param name
 * @param reload    - if true file will be reloaded with new codec.
 */
void EditorBinder::setCodecName(const QString &name, bool reload)
{
    QTextCodec *tmp = QTextCodec::codecForName(name.toAscii());
    if(tmp)
        mCodec = tmp;
    else
        LOG_WARNING("Codec %s not known", name.constData());

    if(reload)
        loadFile();
}



/**
 *  Slot is called when editor's modification flag changed.
 *
 * @param modified
 */
void EditorBinder::onEditorModificationChanged(bool modified)
{
    StatusInt stat = modified ? Modified : Unmodified;
    setStatusInt(stat);
}


/**
 *  Slot is called when file changeg externally.
 *
 */
void EditorBinder::onFileChanged(const QString &)
{
    QFileInfo::refresh();

    if(!exists()) {
        setStatusExt(NotExists);
        mStatusInt = Modified;
    } else if(!isWritable()) {
        setStatusExt(ReadOnly);
        mStatusInt = Unmodified;
    } else {
        setStatusExt(Normal, true);
    }
}


/**
 *  Returns binder's StatusInt.
 *
 * EditorBinder::StatusInt says if editor is modified or not.
 *
 * @return
 */
EditorBinder::StatusInt EditorBinder::getStatusInt() const
{
    return mStatusInt;
}


/**
 *  Returns binder's StatusExt.
 *
 * EditorBinder::StatusExt says if file exists or not, is writable etc.
 *
 * @return
 */
EditorBinder::StatusExt EditorBinder::getStatusExt() const
{
    return mStatusExt;
}


/**
 *  Updates binder's StatusInt
 *
 * @param stat
 * @param force
 */
void EditorBinder::setStatusInt(EditorBinder::StatusInt stat, bool force)
{
    if(mStatusExt == ReadOnly)
        return;

    if( (mStatusInt != stat) || force) {
        // Emit signal with new status before changing internal variable
        // so that receiver can check old status with getStatus().
        emit statusIntChanged(static_cast<int>(stat));
        mStatusInt = stat;
    }
}


/**
 *  Updates binder's StatusExt
 *
 * @param stat
 * @param force
 */
void EditorBinder::setStatusExt(StatusExt stat, bool force)
{
    if( (mStatusExt != stat) || force) {
        // Emit signal with new status before changing internal variable
        // so that receiver can check old status with getStatus().
        emit statusExtChanged(static_cast<int>(stat));
        mStatusExt = stat;
    }
}


/**
 *  Saves file.
 *
 * Other module that calls this function should check if StatusExt is not New.
 */
void EditorBinder::saveFile(bool force)
{
    if(mStatusInt == Unmodified)
        return;

    if(mStatusExt == New)
        LOG_ERROR("Binder shouldn't be New here");

    QString fname = this->absoluteFilePath();
    bool wasExisted = QFile::exists(fname);
    if(wasExisted && AppSettings::instance()->general->isAppBackupCopyEnabled()) {
        QString backupName = QString("~").append(fileName());
        backupName = QFileInfo(absoluteDir(), backupName).absoluteFilePath();
        if(QFile::exists(backupName))
            QFile::remove(backupName);
        QFile::copy(fname, backupName);
    }

    mWatcher->removePath(fname);

    QFile file(fname);
    if(!file.open(QIODevice::WriteOnly))
        LOG_ERROR("Cannot open file %s", fname.constData());

    Editor *edit = mEditors[0];
    file.write(mCodec->fromUnicode(edit->text()));
    file.close();

    edit->setModified(false);
    setStatusInt(Unmodified, true);
    setStatusExt(Normal);

    mWatcher->addPath(fname);

    if(!wasExisted || force) {
        refresh();              // Refresh QFileInfo after file was saved
        emit fileInfoChanged(this);
    }
}


/**
 *  Save file on the given path. Binder's file info part is updated.
 *
 * @param path
 */
void EditorBinder::saveFile(const QString &path)
{
    setFile(path);
    onFileChanged(path);    // Refresh SatusInt and StatusExt

    saveFile(true);
    setLexer(mLexerManager->getLexerName(this));
}


/**
 *  Loads file.
 */
void EditorBinder::loadFile()
{
    if(mEditors.length() == 0)
        LOG_WARNING("Editor doesn't exist");

    if(exists()) {
        QString fileName(this->canonicalFilePath());
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
            LOG_ERROR("Cannot open file %s", fileName.constData());

        QTextStream in(&file);
        in.setCodec(mCodec);
        mEditors[0]->setText(in.readAll());
        file.close();

        setStatusInt(Unmodified);
    }
}


void EditorBinder::setLexer(const QString &name)
{
    if(mLexerName != name) {
        mLexerName = name;
        QsciLexer *lex = mLexerManager->getLexer(mLexerName);
        foreach(Editor *edit, mEditors) {
            edit->setLexer(lex);
        }
        emit lexerChanged(mLexerName);
    }
}

const QString& EditorBinder::getLexerName()
{
    return mLexerName;
}


void EditorBinder::setEolMode(Editor::EolMode eolMode)
{
    if(mEolMode != eolMode) {
        mEolMode = eolMode;
        mEditors[0]->convertEols(mEolMode);
        foreach(Editor *edit, mEditors) {
            edit->setEolMode(mEolMode);
        }
        emit eolChanged(mEolMode);
    }
}

Editor::EolMode EditorBinder::getEolMode()
{
    return mEolMode;
}


Editor::EolMode EditorBinder::guessEol()
{
    Editor::EolMode ret = Editor::EolUnix;
    if(exists()) {
        QString fileName(this->canonicalFilePath());
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
            LOG_ERROR("Cannot open file %s", fileName.constData());

        QString line = QString::fromLocal8Bit(file.readLine().constData());
        if( line.endsWith("\r\n"))
            ret = Editor::EolWindows;
        else if( line.endsWith("\r") )
            ret = Editor::EolMac;

        file.close();
    } else {

#if defined(Q_OS_WIN)
        return Editor::EolWindows;
#elif defined(Q_OS_MAC)
        return Editor::EolMac;
#else
        return Editor::EolUnix;
#endif

    }

    return ret;
}
