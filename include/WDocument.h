
#ifndef __W_DOCUMENT_H_
 #define __W_DOCUMENT_H_


#include "Qsci/qsciscintilla.h"


namespace Wolverine
{


class Document: public QsciScintilla
{
    Q_OBJECT

public:
    explicit Document(QWidget *parent = 0);
    virtual ~Document();

};



}

#endif // __W_DOCUMENT_H_
