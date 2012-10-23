
#include "PageGeneral.h"
#include "ui_PageGeneral.h"

using namespace Wolverine::Settings;

PageGeneral::PageGeneral(CfgAppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageGeneral)
{
    ui->setupUi(this);

    connect(ui->checkBox, SIGNAL(toggled(bool)), &settings->general, SLOT(setValBool(bool)) );
}

PageGeneral::~PageGeneral()
{
    delete ui;
}
