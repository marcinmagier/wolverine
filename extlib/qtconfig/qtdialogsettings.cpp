#include "qtdialogsettings.h"
#include "ui_qtdialogsettings.h"

QtDialogSettings::QtDialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDialogSettings)
{
    ui->setupUi(this);
}

QtDialogSettings::~QtDialogSettings()
{
    delete ui;
}
