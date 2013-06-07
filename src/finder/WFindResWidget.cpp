#include "WFindResWidget.h"
#include "ui_WFindResWidget.h"


using namespace Wolverine;

FindResWidget::FindResWidget(Finder *finder, QWidget *parent) :
    QWidget(parent),
    mFinder(finder),
    ui(new Ui::FindResWidget)
{
    ui->setupUi(this);
}

FindResWidget::~FindResWidget()
{
    delete ui;
}
