
#ifndef __QT_ACTION_MANAGER_WIDGET_H_
 #define __QT_ACTION_MANAGER_WIDGET_H_


#include "qtactionmanager.h"

#include <QWidget>
#include <QTreeWidgetItem>



namespace Ui {
class QtActionManagerWidget;
}

class QtActionManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit QtActionManagerWidget(QMap<QString, QActionMapper > &actionMap, QWidget *parent = 0);
    ~QtActionManagerWidget();
    
private:
    Ui::QtActionManagerWidget *ui;
    QMap<QTreeWidgetItem *, QAction*> m_actionMap;
};

#endif // __QT_ACTION_MANAGER_WIDGET_H_
