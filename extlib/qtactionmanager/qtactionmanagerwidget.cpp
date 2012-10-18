#include "qtactionmanagerwidget.h"
#include "ui_qtactionmanagerwidget.h"

QtActionManagerWidget::QtActionManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtActionManagerWidget)
{
    ui->setupUi(this);
}

QtActionManagerWidget::~QtActionManagerWidget()
{
    delete ui;
}
