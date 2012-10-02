#include "qtmanagedtoolbardialog.h"
#include "ui_qtmanagedtoolbardialog.h"

QtManagedToolBarDialog::QtManagedToolBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtManagedToolBarDialog)
{
    ui->setupUi(this);
}

QtManagedToolBarDialog::~QtManagedToolBarDialog()
{
    delete ui;
}
