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
 *  @file       WEditorBinder.h
 *  @brief      Wolverine::EditorBinder class interface.
 */




#ifndef __W_EDITOR_BINDER_H_
 #define __W_EDITOR_BINDER_H_


#include <QObject>
#include <QList>
#include <QFileInfo>
#include <QIcon>

#include "WEditor.h"



class QTextCodec;
class QFileSystemWatcher;

namespace Wolverine
{

class EditorLexerManager;

typedef QList<Editor*> EditorList;




class EditorBinder : public QObject, public QFileInfo
{
    Q_OBJECT

public:
    enum StatusInt
    {
        Unmodified,
        Modified
    };

    enum StatusExt
    {
        New,
        Normal,
        NotExists,
        ReadOnly
    };

    explicit EditorBinder();
    explicit EditorBinder(const QString &path);
    virtual ~EditorBinder();


    bool hasEditors() const;
    Editor* getEditor();
    EditorList& getEditors();
    Editor* getNewEditor();
    Editor* getLinkedEditor(Editor *editor);
    void removeEditor(Editor *editor);

    StatusInt getStatusInt() const;
    StatusExt getStatusExt() const;


    QString getCodecName();
    void setCodecName(const QString &name, bool reload = false);

    void saveFile(bool force = false);
    void saveFile(const QString &path);
    void loadFile();

    void setLexer(const QString &name);
    const QString& getLexerName();

    void setEolMode(Editor::EolMode eolMode);
    Editor::EolMode getEolMode();

    bool isMonitorModeEnabled();

public slots:
    void enableMonitorMode(bool enable);


signals:
    void statusIntChanged(int);
    void statusExtChanged(int);
    void fileInfoChanged(QFileInfo *fileinfo);
    void lexerChanged(const QString &name);
    void eolChanged(Editor::EolMode eolMode);


private slots:
    void onEditorModificationChanged(bool modified);
    void onFileChanged(const QString&);


private:

    Editor::EolMode guessEol();
    void setStatusInt(StatusInt stat, bool force = false);
    void setStatusExt(StatusExt stat, bool force = false);


    bool mMonitorMode;
    EditorList mEditors;
    StatusInt mStatusInt;
    StatusExt mStatusExt;
    QTextCodec *mCodec;
    QFileSystemWatcher *mWatcher;

    QString mLexerName;
    EditorLexerManager *mLexerManager;

    Editor::EolMode mEolMode;
    static int sNewFileNo;
};



}

#endif // __W_EDITOR_BINDER_H_
