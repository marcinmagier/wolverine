#ifndef WFINDREQWIDGET_H
#define WFINDREQWIDGET_H

#include <QStackedWidget>

class GeneralSettings;

namespace Ui {
class FindReqWidget;
}

namespace Wolverine {


class FindReqWidget : public QStackedWidget
{
    Q_OBJECT
    
public:
    explicit FindReqWidget(QWidget *parent = 0);
    ~FindReqWidget();

    void setCurrentWidget(int idx);
    
private:
    GeneralSettings *mGenSettings;

    Ui::FindReqWidget *ui;
};


};

#endif // WFINDREQWIDGET_H
