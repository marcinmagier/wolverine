
#include "qtactionmanagerwidget.h"
#include "ui_qtactionmanagerwidget.h"

QtActionManagerWidget::QtActionManagerWidget(QtActionManager *actionManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtActionManagerWidget),
    m_actionManager(actionManager)
{
    ui->setupUi(this);
}

QtActionManagerWidget::~QtActionManagerWidget()
{
    delete ui;
}
