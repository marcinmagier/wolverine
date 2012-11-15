#include "qtmanagedtoolbardialog.h"
#include "ui_qtmanagedtoolbardialog.h"


#define QT_MANAGEDTOOLBAR_ICON_WIDGET	":/qtmanagedtoolbar/widget.png"


QtManagedToolBarDialog::QtManagedToolBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtManagedToolBarDialog)
{
    ui->setupUi(this);

    actionsAvailable = 0;
    actionsVisible = 0;

    connect(ui->btnUp, SIGNAL(clicked()), this, SLOT(moveActionUp()));
    connect(ui->btnDown, SIGNAL(clicked()), this, SLOT(moveActionDown()));
    connect(ui->btnToLeft, SIGNAL(clicked()), this, SLOT(moveActionToLeft()));
    connect(ui->btnToRight, SIGNAL(clicked()), this, SLOT(moveActionToRight()));
    connect(ui->listVisible, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(moveActionToLeft(QListWidgetItem*)));
    connect(ui->listAvailable, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(moveActionToRight(QListWidgetItem*)));

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
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

    int retVal = QDialog::exec();

    if(retVal) {
        //User pressed OK, update visible actions
        actionsVisible->clear();
        for(int i=0; i<ui->listVisible->count(); ++i) {
            QListWidgetItem *item = ui->listVisible->item(i);
            if(item->text() == "Separator")
                actionsVisible->append("Separator");
            else
                actionsVisible->append(mActionsVisibleMap[item]);
        }
    }
    return retVal;
}


bool QtManagedToolBarDialog::isActionVisible(QAction *action)
{
    QString name = actionsAvailable->key(action);
    if(actionsVisible->contains(name))
        return true;
    return false;
}

void QtManagedToolBarDialog::fillActionsAvailable()
{
    mActionsAvailableMap.clear();

    //We need to have possibility to add separators
    ui->listAvailable->addItem("Separator");

    foreach( QString name, actionsAvailable->keys()) {
        QAction *action = actionsAvailable->value(name);
        QListWidgetItem *item = new QListWidgetItem(ui->listAvailable);
        item->setText(action->text());
        QIcon icon = action->icon();
        if(icon.isNull())
             // We assume that action without icon is a widget
            item->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_WIDGET));
        else
            item->setIcon(icon);
        if (isActionVisible(action))
            item->setHidden(true);

        mActionsAvailableMap[item] = name;
    }
}

void QtManagedToolBarDialog::fillActionsVisible()
{
    mActionsVisibleMap.clear();

    foreach(QString name, *actionsVisible) {
        if(name == "Separator") {
            ui->listVisible->addItem("Separator");
            continue;
        }
        QListWidgetItem *itemVisible = new QListWidgetItem(ui->listVisible);
        QListWidgetItem *itemAvailable = findActionAvailable(name);
        if (itemAvailable) {
            itemVisible->setText(itemAvailable->text());
            itemVisible->setIcon(itemAvailable->icon());
        }
        mActionsVisibleMap[itemVisible] = name;
    }
}


QListWidgetItem* QtManagedToolBarDialog::findActionAvailable(QString name)
{
    return mActionsAvailableMap.key(name);
}

void QtManagedToolBarDialog::setActionAvailableHidden(QString name, bool hidden)
{
    QListWidgetItem *itemAvailable = findActionAvailable(name);
    if (itemAvailable)
        itemAvailable->setHidden(hidden);
}



void QtManagedToolBarDialog::moveActionToLeft() {
    QListWidgetItem *item = ui->listVisible->currentItem();
    if(item)
        moveActionToLeft(item);
}

void QtManagedToolBarDialog::moveActionToLeft(QListWidgetItem *item) {
    if(item->text() != "Separator") {
        setActionAvailableHidden(mActionsVisibleMap[item], false);
        mActionsVisibleMap.remove(item);
    }
    delete item;
}

void QtManagedToolBarDialog::moveActionToRight() {
    QListWidgetItem *item = ui->listAvailable->currentItem();
    if(item)
        moveActionToRight(item);
}

void QtManagedToolBarDialog::moveActionToRight(QListWidgetItem *item) {
    bool isSeparator = true;

    if(item->text() != "Separator") {
        item->setHidden(true);
        isSeparator = false;
    }
    int row = ui->listVisible->currentRow() + 1; //put new item after item selected
    if(row == 0)
        row = ui->listVisible->count(); //no item selected on listVisible
    ui->listVisible->insertItem(row, item->text());

    QListWidgetItem *newItem = ui->listVisible->item(row);
    newItem->setIcon(item->icon());
    ui->listVisible->setCurrentRow(row);

    if(!isSeparator) {
        QString name = mActionsAvailableMap[item];
        mActionsVisibleMap[newItem] = name;
    }
}

void QtManagedToolBarDialog::moveActionUp() {
    int row = ui->listVisible->currentRow();
    if(row > 0) {
        QListWidgetItem *item = ui->listVisible->takeItem(row);
        row--;
        ui->listVisible->insertItem(row, item);
        ui->listVisible->setCurrentRow(row);
    }
}

void QtManagedToolBarDialog::moveActionDown() {
    int row = ui->listVisible->currentRow();
    if(row >= 0 && row < ui->listVisible->count()-1) {
        QListWidgetItem *item = ui->listVisible->takeItem(row);
        row++;
        ui->listVisible->insertItem(row, item);
        ui->listVisible->setCurrentRow(row);
    }
}

