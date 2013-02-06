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



class QTextCodec;
class QFileSystemWatcher;

namespace Wolverine
{

class Editor;

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


signals:
    void statusIntChanged(int);
    void statusExtChanged(int);


private slots:
    void onEditorModificationChanged(bool modified);
    void onFileChanged(const QString&);


private:
    void loadFile();
    void setStatusInt(StatusInt stat, bool force = false);
    void setStatusExt(StatusExt stat, bool force = false);


    EditorList mEditors;
    StatusInt mStatusInt;
    StatusExt mStatusExt;
    QTextCodec *mCodec;
    QFileSystemWatcher *mWatcher;

    static int sNewFileNo;
};



}

#endif // __W_EDITOR_BINDER_H_
