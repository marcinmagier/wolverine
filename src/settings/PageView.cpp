
#include "PageView.h"
#include "ui_PageView.h"

#include "CfgAppSettings.h"
#include "CfgViewSettings.h"
#include "qtcolorbutton.h"

#include "wolverine_cfg.h"

#include <QColor>


using namespace Wolverine::Settings;

PageView::PageView(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageView)
{
    ui->setupUi(this);

    ui->spinTimeout->setValue(settings->view->getPopupTimeout());
    connect( ui->spinTimeout, SIGNAL(valueChanged(int)),
              settings->view, SLOT(setPopupTimeout(int)), Qt::DirectConnection );

    ui->chboxAnimation->addItems(QString(POPUP_ANIMATION_TYPES).split(" "));
    int idx = ui->chboxAnimation->findText(settings->view->getPopupAnimationType());
    ui->chboxAnimation->setCurrentIndex(idx);
    connect( ui->chboxAnimation, SIGNAL(currentIndexChanged(QString)),
                 settings->view, SLOT(setPopupAnimationType(QString)), Qt::DirectConnection );

    ui->btnBg->setColor(settings->view->getPopupBgColor());
    ui->btnFg->setColor(settings->view->getPopupFgColor());
    connect(      ui->btnBg, SIGNAL(colorChanged(QColor)),
             settings->view, SLOT(setPopupBgColor(QColor)), Qt::DirectConnection );
    connect(      ui->btnFg, SIGNAL(colorChanged(QColor)),
             settings->view, SLOT(setPopupFgColor(QColor)), Qt::DirectConnection );

}

PageView::~PageView()
{
    delete ui;
}

