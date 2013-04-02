#ifndef WFINDREQWIDGET_H
#define WFINDREQWIDGET_H

#include <QWidget>

namespace Ui {
class FindReqWidget;
}

namespace Wolverine {

class FindReqWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FindReqWidget(QWidget *parent = 0);
    ~FindReqWidget();
    
private:
    Ui::FindReqWidget *ui;
};


};

#endif // WFINDREQWIDGET_H
