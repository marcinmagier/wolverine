
#include "PageGeneral.h"
#include "ui_PageGeneral.h"

using namespace Wolverine::Settings;

PageGeneral::PageGeneral(CfgAppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageGeneral)
{
    ui->setupUi(this);

    ui->checkBox->setChecked(settings->general.getValBool());
    connect(ui->checkBox, SIGNAL(toggled(bool)), &settings->general, SLOT(setValBool(bool)) );

    ui->spinBox->setValue(settings->general.getValInt());
    connect(ui->spinBox, SIGNAL(valueChanged(int)), &settings->general, SLOT(setValInt(int)));

    ui->lineEdit->setText(settings->general.getValString());
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), &settings->general, SLOT(setValString(QString)));
}

PageGeneral::~PageGeneral()
{
    delete ui;
}
