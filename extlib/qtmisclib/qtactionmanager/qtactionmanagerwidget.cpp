/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtactionmanagerwidget.cpp
 *  @brief      QtActionManagerWidget class implementation.
 */


#include "qtactionmanagerwidget.h"
#include "qtactionmanager_impl.h"
#include "ui_qtactionmanagerwidget.h"

#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QKeyEvent>

using namespace Impl;




/**
 *  Parameterized constructor.
 *
 * @param actionManager
 * @param parent
 */
QtActionManagerWidget::QtActionManagerWidget(QtActionManager *actionManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtActionManagerWidget),
    mActionManager(actionManager),
    mItemSelected(0)

{
    ui->setupUi(this);

    if(mActionManager->mSchemes.length() > 1) {
        ui->cmbSchemes->addItems(mActionManager->mSchemes);
        int idxCurrentScheme = mActionManager->mSchemes.indexOf(mActionManager->mCurrentScheme);
        ui->cmbSchemes->setCurrentIndex(idxCurrentScheme);
        connect(ui->cmbSchemes, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeCurrentScheme(QString)));
    }
    else {
        // There is only one scheme, we do not need combo.
        ui->lblScheme->setHidden(true);
        ui->cmbSchemes->setHidden(true);
    }


    QStringList headers;
    headers << tr("Command") << tr("Binding") << tr("Category");
    ui->treeActions->setHeaderLabels(headers);
    ui->treeActions->setColumnWidth(1, 130);

    updateUI();


    connect(ui->treeActions, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(onItemDoubleClicked(QTreeWidgetItem*,int)));

}


/**
 *  Destructor.
 */
QtActionManagerWidget::~QtActionManagerWidget()
{
    if(mItemSelected)
        restoreSelected();
    delete ui;
}


/**
 *  Changes current scheme.
 *
 * @param scheme
 */
void QtActionManagerWidget::changeCurrentScheme(QString scheme)
{
    if(mItemSelected)
        restoreSelected();

    mActionManager->setCurrentScheme(scheme);
    ui->treeActions->clear();
    mActionMap.clear();

    updateUI();
}


/**
 *  Starts changing key binding.
 *
 * @param item
 * @param col
 */
void QtActionManagerWidget::onItemDoubleClicked(QTreeWidgetItem *item, int col)
{
    if(item==0 || col!=1)
        return; //No item or it's not Binding column

    if(mItemSelected != 0)
        restoreSelected();
    mItemSelected = item;
    mItemSelected->setText(1, tr("Press a key sequence"));

}


/**
 *  Key event handler.
 *
 * @param event
 */
void QtActionManagerWidget::keyPressEvent(QKeyEvent *event)
{
    if(mItemSelected == 0)
        return;

    if(event->key() == Qt::Key_Escape) {
        restoreSelected();
        return;
    }

    if(event->key()==Qt::Key_Delete) {
        clearSelected();
        return;
    }

    QString key, modifiers;
    bool singleAllowed = false;
    Qt::KeyboardModifiers mods = event->modifiers();
    if ( mods & Qt::ShiftModifier )
        modifiers += "Shift+";
    if ( mods & Qt::ControlModifier )
        modifiers += "Ctrl+";
    if ( mods & Qt::AltModifier )
        modifiers += "Alt+";
    switch ( event->key() ) {
        case Qt::Key_A : key = "A"; break;
        case Qt::Key_B : key = "B"; break;
        case Qt::Key_C : key = "C"; break;
        case Qt::Key_D : key = "D"; break;
        case Qt::Key_E : key = "E"; break;
        case Qt::Key_F : key = "F"; break;
        case Qt::Key_G : key = "G"; break;
        case Qt::Key_H : key = "H"; break;
        case Qt::Key_I : key = "I"; break;
        case Qt::Key_J : key = "J"; break;
        case Qt::Key_K : key = "K"; break;
        case Qt::Key_L : key = "L"; break;
        case Qt::Key_M : key = "M"; break;
        case Qt::Key_N : key = "N"; break;
        case Qt::Key_O : key = "O"; break;
        case Qt::Key_P : key = "P"; break;
        case Qt::Key_Q : key = "Q"; break;
        case Qt::Key_R : key = "R"; break;
        case Qt::Key_S : key = "S"; break;
        case Qt::Key_T : key = "T"; break;
        case Qt::Key_U : key = "U"; break;
        case Qt::Key_V : key = "V"; break;
        case Qt::Key_W : key = "W"; break;
        case Qt::Key_X : key = "X"; break;
        case Qt::Key_Y : key = "Y"; break;
        case Qt::Key_Z : key = "Z"; break;

        case Qt::Key_0 : key = "0"; break;
        case Qt::Key_1 : key = "1"; break;
        case Qt::Key_2 : key = "2"; break;
        case Qt::Key_3 : key = "3"; break;
        case Qt::Key_4 : key = "4"; break;
        case Qt::Key_5 : key = "5"; break;
        case Qt::Key_6 : key = "6"; break;
        case Qt::Key_7 : key = "7"; break;
        case Qt::Key_8 : key = "8"; break;
        case Qt::Key_9 : key = "9"; break;

        case Qt::Key_F1 :         key = "F1"; singleAllowed = true; break;
        case Qt::Key_F2 :         key = "F2"; singleAllowed = true; break;
        case Qt::Key_F3 :         key = "F3"; singleAllowed = true; break;
        case Qt::Key_F4 :         key = "F4"; singleAllowed = true; break;
        case Qt::Key_F5 :         key = "F5"; singleAllowed = true; break;
        case Qt::Key_F6 :         key = "F6"; singleAllowed = true; break;
        case Qt::Key_F7 :         key = "F7"; singleAllowed = true; break;
        case Qt::Key_F8 :         key = "F8"; singleAllowed = true; break;
        case Qt::Key_F9 :         key = "F9"; singleAllowed = true; break;
        case Qt::Key_F10 :        key = "F10"; singleAllowed = true; break;
        case Qt::Key_F11 :        key = "F11"; singleAllowed = true; break;
        case Qt::Key_F12 :        key = "F12"; singleAllowed = true; break;
        case Qt::Key_Escape :     key = "Esc"; singleAllowed = true; break;

        case Qt::Key_Apostrophe : key = "'"; break;
        case Qt::Key_QuoteDbl :   key = "'"; break;
        case Qt::Key_Equal :      key = "="; break;
        case Qt::Key_Minus :      key = "-"; break;
        case Qt::Key_Underscore : key = "-"; break;
        case Qt::Key_Comma :      key = ","; break;
        case Qt::Key_Less:        key = ","; break;
        case Qt::Key_Period :     key = "."; break;
        case Qt::Key_Greater:     key = "."; break;
        case Qt::Key_Semicolon:   key = ";"; break;
        case Qt::Key_Colon:       key = ";"; break;

        case Qt::Key_Exclam:      key = modifiers.contains("Shift") ? "1" : "!"; break;
        case Qt::Key_At:          key = modifiers.contains("Shift") ? "2" : "@"; break;
        case Qt::Key_NumberSign:  key = modifiers.contains("Shift") ? "3" : "#"; break;
        case Qt::Key_Dollar:      key = modifiers.contains("Shift") ? "4" : "$"; break;
        case Qt::Key_Percent:     key = modifiers.contains("Shift") ? "5" : "%"; break;
        case Qt::Key_AsciiCircum: key = modifiers.contains("Shift") ? "6" : "^"; break;
        case Qt::Key_Ampersand:   key = modifiers.contains("Shift") ? "7" : "&"; break;
        case Qt::Key_Asterisk:    key = modifiers.contains("Shift") ? "8" : "*"; break;
        case Qt::Key_ParenLeft:   key = modifiers.contains("Shift") ? "9" : "("; break;
        case Qt::Key_ParenRight:  key = modifiers.contains("Shift") ? "0" : ")"; break;
        case Qt::Key_Plus:        key = modifiers.contains("Shift") ? "=" : "+"; break;

        case Qt::Key_Left:        key = "Left"; break;
        case Qt::Key_Right:       key = "Right"; break;
        case Qt::Key_Up:          key = "Up"; break;
        case Qt::Key_Down:        key = "Down"; break;

        default: return;
    }
    if ( modifiers.isEmpty() && !singleAllowed ) {
        return;
    }

    QKeySequence newShortcut(modifiers+key);
    QTreeWidgetItem *duplicateShortcut = findShortcut(newShortcut.toString());
    QString scheme = mActionManager->mCurrentScheme;

    if(duplicateShortcut) {
        QString text = tr("This shortcut \"%1\" is already assigned to command \"%2\".\n"
                          "Do you want to reassign it to the current command?").arg(newShortcut.toString()).arg(duplicateShortcut->text(0));
        int retVal = QMessageBox::warning(this, tr("Warning"), text, QMessageBox::Yes, QMessageBox::No);
        if(retVal == QMessageBox::No) {
            restoreSelected();
            return;
        }
        else {
            duplicateShortcut->setText(1, "");
            QtAction *qtAction = mActionMap[duplicateShortcut];
            qtAction->action->setShortcut(QKeySequence(""));
            qtAction->schemeBinding[scheme] = "";
        }
    }

    QtAction *qtAction = mActionMap[mItemSelected];
    qtAction->action->setShortcut(newShortcut);
    qtAction->schemeBinding[scheme] = newShortcut.toString();
    mItemSelected->setText(1, newShortcut.toString());
    mItemSelected = 0;
}


/**
 *  Refreshes ui.
 */
void QtActionManagerWidget::updateUI()
{
    QString scheme = mActionManager->mCurrentScheme;

    foreach(QString category, mActionManager->mActionCategories.keys()) {
        QtActionsMap qtactions = mActionManager->mActionCategories.value(category);

        foreach(QString name, qtactions.keys()) {
            QtAction *qtAction = qtactions[name];
            QKeySequence shortcut = qtAction->shortcut(scheme);
            QStringList row;
            row << qtAction->action->text() << shortcut.toString() << category;
            QTreeWidgetItem *item = new QTreeWidgetItem(row);
            item->setIcon(0, qtAction->action->icon());
            ui->treeActions->addTopLevelItem(item);

            mActionMap.insert(item, qtAction);
        }

    }
}


/**
 *  Stops changing key binding - user pressed Delete.
 *
 */
void QtActionManagerWidget::clearSelected()
{
    if(mItemSelected != 0) {
        QtAction *qtaction = mActionMap[mItemSelected];
        qtaction->action->setShortcut(QKeySequence(""));
        mItemSelected->setText(1, "");
        mItemSelected = 0;
    }
}


/**
 *  Stops changing key binding - user pressed Escape.
 */
void QtActionManagerWidget::restoreSelected()
{
    if(mItemSelected != 0) {
        QtAction *qtaction = mActionMap[mItemSelected];
        QString scheme = mActionManager->mCurrentScheme;
        mItemSelected->setText(1, qtaction->shortcut(scheme));
        mItemSelected = 0;
    }
}


/**
 *  Finds shortcut on the list.
 *
 * @param shortcut
 * @return
 */
QTreeWidgetItem* QtActionManagerWidget::findShortcut(QString shortcut)
{
    int count = ui->treeActions->topLevelItemCount();
    for (int i = 0; i < count; ++i) {
        QTreeWidgetItem* item =ui->treeActions->topLevelItem(i);
        if(shortcut == item->text(1))
            return item;
    }
    return 0;
}
