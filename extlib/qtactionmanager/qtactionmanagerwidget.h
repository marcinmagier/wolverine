#ifndef QTACTIONMANAGERWIDGET_H
#define QTACTIONMANAGERWIDGET_H

#include <QWidget>

namespace Ui {
class QtActionManagerWidget;
}

class QtActionManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit QtActionManagerWidget(QWidget *parent = 0);
    ~QtActionManagerWidget();
    
private:
    Ui::QtActionManagerWidget *ui;
};

#endif // QTACTIONMANAGERWIDGET_H
