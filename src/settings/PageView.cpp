
#include "PageView.h"
#include "ui_PageView.h"

#include "CfgAppSettings.h"

#include <QColor>


using namespace Wolverine::Settings;

PageView::PageView(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageView)
{
    ui->setupUi(this);



}

PageView::~PageView()
{
    delete ui;
}

