#ifndef WFINDRESWIDGET_H
#define WFINDRESWIDGET_H

#include <QWidget>

namespace Ui {
class FindResWidget;
}

namespace Wolverine
{

class Finder;

class FindResWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FindResWidget(Finder *finder, QWidget *parent = 0);
    ~FindResWidget();
    
private:
    Finder *mFinder;
    Ui::FindResWidget *ui;
};

}

#endif // WFINDRESWIDGET_H
