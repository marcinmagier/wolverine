
#ifndef __QT_MANAGED_TOOLBAR_DIALOG_H_
 #define __QT_MANAGED_TOOLBAR_DIALOG_H_

class QAction;
class QString;
class QStringList;
class QListWidgetItem;

#include <QMap>
#include <QDialog>

namespace Ui {
class QtManagedToolBarDialog;
}


typedef QMap<QString, QAction*> QtActionNameMap;


class QtManagedToolBarDialog : public QDialog
{
    Q_OBJECT


public:
    explicit QtManagedToolBarDialog(QWidget *parent = 0);
    ~QtManagedToolBarDialog();

    int exec(const QtActionNameMap *actionsAvailable, QStringList *actionsVisible);


private slots:
    void moveActionUp();
    void moveActionDown();
    void moveActionToLeft();
    void moveActionToLeft(QListWidgetItem *item);
    void moveActionToRight();
    void moveActionToRight(QListWidgetItem *item);


private:
    void fillActionsAvailable(const QtActionNameMap *actionsAvailable, const QStringList *actionsVisible);
    void fillActionsVisible(const QStringList *actionsVisible);

    QMap<QListWidgetItem*, QString> mActionsAvailableMap;
    QMap<QListWidgetItem*, QString> mActionsVisibleMap;

    Ui::QtManagedToolBarDialog *ui;
};

#endif // __QT_MANAGED_TOOLBAR_DIALOG_H_
