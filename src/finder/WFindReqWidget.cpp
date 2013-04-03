#include "WFindReqWidget.h"
#include "ui_WFindReqWidget.h"



using namespace Wolverine;

FindReqWidget::FindReqWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReqWidget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    ui->btnCaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btnWholeWords->setIcon(QIcon(":/search_words.png"));
    ui->btnRegexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btnReverseDirection->setIcon(QIcon(":/search_reverse.png"));
    ui->btnWrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btnInSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btnMark->setIcon(QIcon(":/search_mark.png"));

}

FindReqWidget::~FindReqWidget()
{
    delete ui;
}
