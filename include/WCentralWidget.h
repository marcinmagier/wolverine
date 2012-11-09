
#ifndef __W_CENTRAL_WIDGET_H_
 #define __W_CENTRAL_WIDGET_H_


class QHBoxLayout;
class QSplitter;
class QTabWidget;
class QsciScintilla;


#include <QWidget>

namespace Wolverine
{

class Document;



class CentralWidget: public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0);
    virtual ~CentralWidget();

private:
    QHBoxLayout *layout;
    QSplitter *splitter;
    QTabWidget *panelLeft;
    QTabWidget *panelRight;

    Document *editor;
};



}









#endif // __W_CENTRAL_WIDGET_H_
