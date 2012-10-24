
#include "qtactionmanagerwidget.h"
#include "ui_qtactionmanagerwidget.h"

QtActionManagerWidget::QtActionManagerWidget(QMap<QString, QActionMapper > &actionMap, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtActionManagerWidget)
{
    ui->setupUi(this);
}

QtActionManagerWidget::~QtActionManagerWidget()
{
    delete ui;
}
