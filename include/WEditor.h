
#ifndef __W_EDITOR_H_
 #define __W_EDITOR_H_


#include "Qsci/qsciscintilla.h"


namespace Wolverine
{

class EditorBinder;

class Editor: public QsciScintilla
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = 0);
    explicit Editor(EditorBinder *doc, QWidget *parent = 0);
    virtual ~Editor();

    Editor* getLinkedCopy();
    static void removeEditor(Editor *editor);

    void setBinder(EditorBinder* doc);
    EditorBinder* getBinder();


signals:
    void focusReceived();


protected:
    virtual void focusInEvent(QFocusEvent *event);

private:
    void initialize();

    EditorBinder *mBinder;

};



}

#endif // __W_EDITOR_H_
