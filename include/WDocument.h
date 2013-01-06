
#ifndef __W_DOCUMENT_H_
 #define __W_DOCUMENT_H_


#include <QObject>


namespace Wolverine
{


class Document: public QObject
{
    Q_OBJECT

public:
    explicit Document();
    virtual ~Document();

};



}

#endif // __W_DOCUMENT_H_
