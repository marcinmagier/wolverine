#include "WFindReqWidget.h"
#include "ui_WFindReqWidget.h"



using namespace Wolverine;

FindReqWidget::FindReqWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::FindReqWidget)
{
    ui->setupUi(this);

    ui->btn0CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn0CaseSensitive->setToolTip(tr("Case Sensitive"));
    ui->btn1CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn1CaseSensitive->setToolTip(tr("Case Sensitive"));
    ui->btn2CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn2CaseSensitive->setToolTip(tr("Case Sensitive"));

    ui->btn0Words->setIcon(QIcon(":/search_words.png"));
    ui->btn0Words->setToolTip(tr("Whole Words"));
    ui->btn1Words->setIcon(QIcon(":/search_words.png"));
    ui->btn1Words->setToolTip(tr("Whole Words"));
    ui->btn2Words->setIcon(QIcon(":/search_words.png"));
    ui->btn2Words->setToolTip(tr("Whole Words"));

    ui->btn0Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn0Regexp->setToolTip(tr("Regular Expression"));
    ui->btn1Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn1Regexp->setToolTip(tr("Regular Expression"));
    ui->btn2Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn2Regexp->setToolTip(tr("Regular Expression"));

    ui->btn0Reverse->setIcon(QIcon(":/search_reverse.png"));
    ui->btn0Reverse->setToolTip(tr("Reverse Direction"));
    ui->btn1Reverse->setIcon(QIcon(":/search_reverse.png"));
    ui->btn1Reverse->setToolTip(tr("Reverse Direction"));

    ui->btn0Wrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btn0Wrap->setToolTip(tr("Wrap"));
    ui->btn1Wrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btn1Wrap->setToolTip(tr("Wrap"));

    ui->btn0InSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btn0InSelection->setToolTip(tr("In Selection"));
    ui->btn1InSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btn1InSelection->setToolTip(tr("In Selection"));

    ui->btn0Mark->setIcon(QIcon(":/search_mark.png"));
    ui->btn0Mark->setToolTip("Bookmark Line");

    ui->btn2InSubDirs->setIcon(QIcon(":/search_subdirs.png"));
    ui->btn2InSubDirs->setToolTip(tr("Search in sub-folders"));

    ui->btn2InHiddenDirs->setIcon(QIcon(":/search_hidden.png"));
    ui->btn2InHiddenDirs->setToolTip(tr("Search in hidden folders"));

    ui->btn2SelectDir->setIcon(QIcon(":/search_select_dir.png"));
    ui->btn2SelectDir->setToolTip(tr("Select Directory"));

    ui->btn2CurrentDir->setIcon(QIcon(":/search_current_dir.png"));
    ui->btn2CurrentDir->setToolTip(tr("Select Current Document's Directory"));

}

FindReqWidget::~FindReqWidget()
{
    delete ui;
}

void FindReqWidget::setCurrentWidget(int idx)
{
    setCurrentIndex(idx);
}
