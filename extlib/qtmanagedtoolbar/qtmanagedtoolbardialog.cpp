#include "qtmanagedtoolbardialog.h"
#include "ui_qtmanagedtoolbardialog.h"

QtManagedToolBarDialog::QtManagedToolBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtManagedToolBarDialog)
{
    ui->setupUi(this);

    actionsAvailable = 0;
    actionsVisible = 0;
}

QtManagedToolBarDialog::~QtManagedToolBarDialog()
{
    delete ui;
}

int QtManagedToolBarDialog::exec()
{
    if (actionsAvailable == 0)
        return QDialog::Rejected;
    if (actionsVisible == 0)
        return QDialog::Rejected;

    fillActionsAvailable();
    fillActionsVisible();

    return QDialog::exec();
}


bool QtManagedToolBarDialog::isActionVisible(QAction *action)
{
    for (int i=0; i<actionsVisible->size(); ++i) {
        if (actionsVisible->at(i) == action->text())
           return true;
    }
    return false;
}

void QtManagedToolBarDialog::fillActionsAvailable()
{
    //We need to have possibility to add separators
    ui->listAvailable->addItem("Separator");

    for(int i=0; i<actionsAvailable->length(); i++) {
        QAction *action = actionsAvailable->at(i);
        QListWidgetItem *item = new QListWidgetItem(ui->listAvailable);
        item->setText(action->text());
        item->setIcon(action->icon());
        if (!isActionVisible(action))
            item->setHidden(true);
    }
}

void QtManagedToolBarDialog::fillActionsVisible()
{
    for (int i=0; i<actionsVisible->size(); ++i) {
        if (actionsVisible->at(i) == "Separator") {
            ui->listVisible->addItem("Separator");
            continue;
        }
        QListWidgetItem *itemVisible = new QListWidgetItem(ui->listVisible);
        itemVisible->setText(actionsVisible->at(i));
        QListWidgetItem *itemAvailable = findActionAvailable(itemVisible->text());
        if (itemAvailable)
            itemVisible->setIcon(itemAvailable->icon());
    }
}


QListWidgetItem* QtManagedToolBarDialog::findActionAvailable(QString name)
{
    for (int i=0; i< ui->listAvailable->count(); i++) {
        QListWidgetItem *item = ui->listAvailable->item(i);
        if (item->text() == name) {
            return item;
        }
    }
    return 0;
}


void QtManagedToolBarDialog::setActionAvailableHidden(QString name, bool hidden)
{
    QListWidgetItem *itemAvailable = findActionAvailable(name);
    if (itemAvailable)
        itemAvailable->setHidden(hidden);
}
