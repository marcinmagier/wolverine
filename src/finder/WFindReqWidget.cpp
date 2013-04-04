#include "WFindReqWidget.h"
#include "ui_WFindReqWidget.h"



using namespace Wolverine;

FindReqWidget::FindReqWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::FindReqWidget)
{
    ui->setupUi(this);
/*
    ui->btnCaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btnCaseSensitive->setToolTip(tr("Case Sensitive"));
    ui->btnWholeWords->setIcon(QIcon(":/search_words.png"));
    ui->btnWholeWords->setToolTip(tr("Whole Words"));
    ui->btnRegexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btnRegexp->setToolTip(tr("Regular Expression"));
    ui->btnReverseDirection->setIcon(QIcon(":/search_reverse.png"));
    ui->btnReverseDirection->setToolTip(tr("Reverse Direction"));
    ui->btnWrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btnWrap->setToolTip(tr("Wrap"));
    ui->btnInSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btnInSelection->setToolTip(tr("In Selection"));
    ui->btnMark->setIcon(QIcon(":/search_mark.png"));
    ui->btnMark->setToolTip("Bookmark Line");

    ui->btnCaseSensitive2->setIcon(QIcon(":/search_sensitive.png"));
    ui->btnCaseSensitive2->setToolTip(tr("Case Sensitive"));
    ui->btnWholeWords2->setIcon(QIcon(":/search_words.png"));
    ui->btnWholeWords2->setToolTip(tr("Whole Words"));
    ui->btnRegexp2->setIcon(QIcon(":/search_regexp.png"));
    ui->btnRegexp2->setToolTip(tr("Regular Expression"));
    ui->btnReverseDirection2->setIcon(QIcon(":/search_reverse.png"));
    ui->btnReverseDirection2->setToolTip(tr("Reverse Direction"));
    ui->btnWrap2->setIcon(QIcon(":/search_wrap.png"));
    ui->btnWrap2->setToolTip(tr("Wrap"));
    ui->btnInSelection2->setIcon(QIcon(":/search_selection.png"));
    ui->btnInSelection2->setToolTip(tr("In Selection"));
*/

}

FindReqWidget::~FindReqWidget()
{
    delete ui;
}

void FindReqWidget::setCurrentWidget(int idx)
{
    setCurrentIndex(idx);
}
