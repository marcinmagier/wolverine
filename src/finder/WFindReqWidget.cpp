#include "WFindReqWidget.h"
#include "ui_WFindReqWidget.h"



using namespace Wolverine;

FindReqWidget::FindReqWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReqWidget)
{
    ui->setupUi(this);

}

FindReqWidget::~FindReqWidget()
{
    delete ui;
}
