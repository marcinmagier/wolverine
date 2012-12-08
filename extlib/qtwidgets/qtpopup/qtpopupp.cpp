#include "qtpopupp.h"
#include "ui_qtpopupp.h"

QtPopupp::QtPopupp(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QtPopupp)
{
    ui->setupUi(this);
}

QtPopupp::~QtPopupp()
{
    delete ui;
}
