#ifndef __MANAGED_TOOLBAR_DIALOG_H_
 #define __MANAGED_TOOLBAR_DIALOG_H_

#include <QDialog>

class QListWidgetItem;

namespace Ui {
class QtManagedToolBarDialog;
}

class QtManagedToolBarDialog : public QDialog
{
    Q_OBJECT


public:
    explicit QtManagedToolBarDialog(QWidget *parent = 0);
    ~QtManagedToolBarDialog();

    int exec();

    QList<QAction*> *actionsAvailable;
    QStringList *actionsVisible;


private slots:
    void moveActionUp();
    void moveActionDown();
    void moveActionToLeft();
    void moveActionToLeft(QListWidgetItem *item);
    void moveActionToRight();
    void moveActionToRight(QListWidgetItem *item);


private:
    bool isActionVisible(QAction *action);
    void fillActionsAvailable();
    void fillActionsVisible();
    QListWidgetItem* findActionAvailable(QString name);
    void setActionAvailableHidden(QString name, bool visible);


    Ui::QtManagedToolBarDialog *ui;
};

#endif // __MANAGED_TOOLBAR_DIALOG_H_
