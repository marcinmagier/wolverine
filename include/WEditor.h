
#ifndef __W_EDITOR_H_
 #define __W_EDITOR_H_


#include "Qsci/qsciscintilla.h"


namespace Wolverine
{

class Document;

class Editor: public QsciScintilla
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    explicit Editor(Document *doc, QWidget *parent = 0);
    virtual ~Editor();

    void setDocument(Document* doc);
    Document* getDocument();


private:
    Document *mDocument;

};



}

#endif // __W_EDITOR_H_