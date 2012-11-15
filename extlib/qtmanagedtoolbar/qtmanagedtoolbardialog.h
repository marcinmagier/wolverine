
#ifndef __QT_MANAGED_TOOLBAR_DIALOG_H_
 #define __QT_MANAGED_TOOLBAR_DIALOG_H_

class QListWidgetItem;

#include <QMap>
#include <QDialog>

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

    QMap<QString, QAction*> *actionsAvailable;
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

    QMap<QListWidgetItem*, QString> mActionsAvailableMap;
    QMap<QListWidgetItem*, QString> mActionsVisibleMap;

    Ui::QtManagedToolBarDialog *ui;
};

#endif // __QT_MANAGED_TOOLBAR_DIALOG_H_
