
#ifndef __QT_ACTION_MANAGER_WIDGET_H_
 #define __QT_ACTION_MANAGER_WIDGET_H_


class QTreeWidgetItem;
class QKeyEvent;

#include "qtaction.h"

#include <QWidget>

namespace Private {
class QtActionManager;
}

namespace Ui {
class QtActionManagerWidget;
}

class QtActionManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit QtActionManagerWidget(Private::QtActionManager *actionManager, QWidget *parent = 0);
    ~QtActionManagerWidget();


public slots:
    void changeCurrentScheme(QString scheme);
    void onItemDoubleClicked(QTreeWidgetItem* item, int col);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void updateUI();
    void clearSelected();
    void restoreSelected();
    QTreeWidgetItem* findShortcut(QString shortcut);

    Ui::QtActionManagerWidget *ui;
    Private::QtActionManager *m_actionManager;
    QMap<QTreeWidgetItem *, QtAction*> m_actionMap;
    QTreeWidgetItem *m_itemSelected;
};

#endif // __QT_ACTION_MANAGER_WIDGET_H_
