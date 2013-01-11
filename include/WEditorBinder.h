
#ifndef __W_DOCUMENT_H_
 #define __W_DOCUMENT_H_


#include <QObject>
#include <QList>
#include <QFileInfo>
#include <QIcon>




namespace Wolverine
{

class Editor;

typedef QList<Editor*> EditorList;




class EditorBinder: public QObject, public QFileInfo
{
    Q_OBJECT

public:
    explicit EditorBinder();
    explicit EditorBinder(const QString &path);
    virtual ~EditorBinder();


    bool hasEditors() const;
    Editor* getEditor();
    EditorList& getEditors();
    Editor* getNewEditor();
    Editor* getLinkedEditor(Editor *editor);
    void removeEditor(Editor *editor);

    QIcon getIcon() const;



private:
    EditorList mEditors;

    static int sNewFileNo;
};



}

#endif // __W_DOCUMENT_H_
