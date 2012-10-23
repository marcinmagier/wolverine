
#include "qtdialogsettings.h"
#include "ui_qtdialogsettings.h"

QtDialogSettings::QtDialogSettings(QtConfig *config, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDialogSettings),
    m_config(config)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

QtDialogSettings::~QtDialogSettings()
{
    delete ui;
}

void QtDialogSettings::addSettingsPage(const QString &name, QWidget *page)
{

}

void QtDialogSettings::addSettingsPage(const QString &name, const QString &parent, QWidget *page)
{

}

void QtDialogSettings::addPluginSettingsPage(const QString &name, QWidget *page)
{

}
