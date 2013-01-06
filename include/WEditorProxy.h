
#ifndef __W_EDITOR_PROXY_H_
 #define __W_EDITOR_PROXY_H_


#include <QObject>


namespace Wolverine
{


class EditorProxy: public QObject
{
    Q_OBJECT

public:
    explicit EditorProxy();
    virtual ~EditorProxy();

};



}

#endif // __W_EDITOR_PROXY_H_
