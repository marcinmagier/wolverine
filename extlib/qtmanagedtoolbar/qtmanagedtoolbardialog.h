/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/


#ifndef __QT_MANAGED_TOOLBAR_DIALOG_H_
 #define __QT_MANAGED_TOOLBAR_DIALOG_H_


class QAction;
class QString;
class QStringList;
class QListWidgetItem;

namespace Ui {
class QtManagedToolBarDialog;
}

#include <QMap>
#include <QDialog>



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
