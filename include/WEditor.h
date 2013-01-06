
#ifndef __W_EDITOR_H_
 #define __W_EDITOR_H_


#include "Qsci/qsciscintilla.h"


namespace Wolverine
{


class Editor: public QsciScintilla
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    virtual ~Editor();

};



}

#endif // __W_EDITOR_H_
