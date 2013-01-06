
#ifndef __W_EDITOR_PROXY_H_
 #define __W_EDITOR_PROXY_H_


#include <QObject>


namespace Wolverine
{

class Editor;


class EditorProxy: public QObject
{
    Q_OBJECT

public:
    explicit EditorProxy();
    virtual ~EditorProxy();

public slots:
    void setCurrentEditor(Editor *editor);

signals:
    void currentEditorChanged(Editor *editor);


private:
    Editor *mCurrentEditor;

};



}

#endif // __W_EDITOR_PROXY_H_
