/**************************************************************************************************
**
**  Copyright (C) 2012-2013 Magier Marcin
**
**  This program is free software: you can redistribute it and/or modify it under the terms
**  of the GNU General Public License as published by the Free Software Foundation,
**  either version 3 of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
**  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**  See the GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************************************/

/**
 *  @file       qtmanagedtoolbardialog.cpp
 *  @brief      QtManagedToolbarDialog class implementation.
 */


#include "qtmanagedwidgetsdialog.h"
#include "ui_qtmanagedwidgetsdialog.h"



#define QT_MANAGEDTOOLBAR_ICON_WIDGET	":/qtmanagedwidgets/widget.png"




/**
 *  Default constructor.
 *
 * @param parent
 */
QtManagedWidgetsDialog::QtManagedWidgetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtManagedWidgetsDialog)
{
    ui->setupUi(this);

    connect(ui->btnUp, SIGNAL(clicked()), this, SLOT(moveActionUp()));
    connect(ui->btnDown, SIGNAL(clicked()), this, SLOT(moveActionDown()));
    connect(ui->btnToLeft, SIGNAL(clicked()), this, SLOT(moveActionToLeft()));
    connect(ui->btnToRight, SIGNAL(clicked()), this, SLOT(moveActionToRight()));
    connect(ui->listVisible, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(moveActionToLeft(QListWidgetItem*)));
    connect(ui->listAvailable, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(moveActionToRight(QListWidgetItem*)));

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}


/**
 *   Default destructor.
 */
QtManagedWidgetsDialog::~QtManagedWidgetsDialog()
{
    delete ui;
}


/**
 * Shows dialog.
 *
 * @param actionsAvailable
 * @param actionsVisible
 * @return
 */
int QtManagedWidgetsDialog::exec(const QtActionNameMap *actionsAvailable, QStringList *actionsVisible)
{
    if (actionsAvailable == 0)
        return QDialog::Rejected;
    if (actionsVisible == 0)
        return QDialog::Rejected;

    fillActionsAvailable(actionsAvailable, actionsVisible);
    fillActionsVisible(actionsVisible);

    int retVal = QDialog::exec();

    if(retVal) {
        //User pressed OK, update visible actions
        actionsVisible->clear();
        for(int i=0; i<ui->listVisible->count(); ++i) {
            QListWidgetItem *item = ui->listVisible->item(i);
            actionsVisible->append(mActionsVisibleMap[item]);
        }
    }
    return retVal;
}


/**
 *  Fills "available" list.
 *
 * @param actionsAvailable
 * @param actionsVisible
 */
void QtManagedWidgetsDialog::fillActionsAvailable(const QtActionNameMap *actionsAvailable, const QStringList *actionsVisible)
{
    mActionsAvailableMap.clear();

    //We need to have possibility to add separators
    QListWidgetItem *item = new QListWidgetItem(ui->listAvailable);
    item->setText(tr("Separator"));
    mActionsAvailableMap[item] = "Separator";

    foreach( QString name, actionsAvailable->keys()) {
        QAction *action = actionsAvailable->value(name);
        item = new QListWidgetItem(ui->listAvailable);
        item->setText(action->text());
        QIcon icon = action->icon();
        if(icon.isNull())
             // We assume that action without icon is a widget
            item->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_WIDGET));
        else
            item->setIcon(icon);

        if (actionsVisible->contains(name))
            item->setHidden(true);

        mActionsAvailableMap[item] = name;
    }
}


/**
 *  Fills "visable" list.
 *
 * @param actionsVisible
 */
void QtManagedWidgetsDialog::fillActionsVisible(const QStringList *actionsVisible)
{
    mActionsVisibleMap.clear();

    foreach(QString name, *actionsVisible) {
        QListWidgetItem *itemVisible;
        if(name == "Separator") {
            itemVisible = new QListWidgetItem(ui->listVisible);
            itemVisible->setText(tr("Separator"));
            mActionsVisibleMap[itemVisible] = "Separator";
            continue;
        }
        itemVisible = new QListWidgetItem(ui->listVisible);
        QListWidgetItem *itemAvailable = mActionsAvailableMap.key(name);
        if (itemAvailable) {
            itemVisible->setText(itemAvailable->text());
            itemVisible->setIcon(itemAvailable->icon());
        }
        mActionsVisibleMap[itemVisible] = name;
    }
}



/**
 *  Moves action from the "visable" list.
 */
void QtManagedWidgetsDialog::moveActionToLeft() {
    QListWidgetItem *item = ui->listVisible->currentItem();
    if(item)
        moveActionToLeft(item);
}


/**
 *  Moves action from the "visable" list.
 *
 * @param item
 */
void QtManagedWidgetsDialog::moveActionToLeft(QListWidgetItem *item) {
    QString name = mActionsVisibleMap[item];
    if(name != "Separator") {
        QListWidgetItem *itemAvailable = mActionsAvailableMap.key(name);
        if (itemAvailable)
            itemAvailable->setHidden(false);
    }
    mActionsVisibleMap.remove(item);
    delete item;
}


/**
 *  Moves action to the "visable" list.
 */
void QtManagedWidgetsDialog::moveActionToRight() {
    QListWidgetItem *item = ui->listAvailable->currentItem();
    if(item)
        moveActionToRight(item);
}


/**
 * Moves action to the "visable" list.
 *
 * @param item
 */
void QtManagedWidgetsDialog::moveActionToRight(QListWidgetItem *item) {
    if(mActionsAvailableMap[item] != "Separator") {
        item->setHidden(true);
    }
    int row = ui->listVisible->currentRow() + 1; //put new item after item selected
    if(row == 0)
        row = ui->listVisible->count(); //no item selected on listVisible
    ui->listVisible->insertItem(row, item->text());

    QListWidgetItem *newItem = ui->listVisible->item(row);
    newItem->setIcon(item->icon());
    ui->listVisible->setCurrentRow(row);

    QString name = mActionsAvailableMap[item];
    mActionsVisibleMap[newItem] = name;
}


/**
 *  Moves action up.
 */
void QtManagedWidgetsDialog::moveActionUp() {
    int row = ui->listVisible->currentRow();
    if(row > 0) {
        QListWidgetItem *item = ui->listVisible->takeItem(row);
        row--;
        ui->listVisible->insertItem(row, item);
        ui->listVisible->setCurrentRow(row);
    }
}


/**
 *  Moves action down.
 */
void QtManagedWidgetsDialog::moveActionDown() {
    int row = ui->listVisible->currentRow();
    if(row >= 0 && row < ui->listVisible->count()-1) {
        QListWidgetItem *item = ui->listVisible->takeItem(row);
        row++;
        ui->listVisible->insertItem(row, item);
        ui->listVisible->setCurrentRow(row);
    }
}

