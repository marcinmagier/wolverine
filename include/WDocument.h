
#ifndef __W_DOCUMENT_H_
 #define __W_DOCUMENT_H_


#include <QObject>
#include <QList>
#include <QFileInfo>




namespace Wolverine
{

class Editor;

typedef QList<Editor*> EditorList;




class Document: public QObject
{
    Q_OBJECT

public:
    explicit Document();
    explicit Document(const QString &path);
    virtual ~Document();

    QString getFileName() const;
    QString getAbsoluteFilePath() const;
    bool exists() const;
    bool isWritable() const;

    bool hasEditors() const;
    Editor* getEditor();
    Editor* getNewEditor();

private:
    QFileInfo mFile;
    EditorList mEditors;

    static int sNewFileNo;
};



}

#endif // __W_DOCUMENT_H_
