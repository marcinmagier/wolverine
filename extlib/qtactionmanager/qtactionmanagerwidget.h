
#ifndef __QT_ACTION_MANAGER_WIDGET_H_
 #define __QT_ACTION_MANAGER_WIDGET_H_


class QTreeWidgetItem;


#include "qtactionmanager.h"

#include <QWidget>



namespace Ui {
class QtActionManagerWidget;
}

class QtActionManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit QtActionManagerWidget(QtActionManager *actionManager, QWidget *parent = 0);
    ~QtActionManagerWidget();
    
private:
    Ui::QtActionManagerWidget *ui;
    QMap<QTreeWidgetItem *, QtAction*> m_actionMap;
    QtActionManager *m_actionManager;
};

#endif // __QT_ACTION_MANAGER_WIDGET_H_
