
#include "PageView.h"
#include "ui_PageView.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"
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


    ui->checkTabsMovable->setChecked( settings->view->isTabBarMovable() );
    connect( ui->checkTabsMovable, SIGNAL(toggled(bool)),
                    settings->view, SLOT(setTabBarMovable(bool)), Qt::DirectConnection );

    ui->checkCloseBtnVisible->setChecked( settings->view->isTabBarCloseVisible() );
    connect( ui->checkCloseBtnVisible, SIGNAL(toggled(bool)),
                       settings->view, SLOT(setTabBarCloseVisible(bool)), Qt::DirectConnection );

    ui->checkDoubleClkClose->setChecked( settings->view->isTabBarDoubleClkClose() );
    connect( ui->checkDoubleClkClose, SIGNAL(toggled(bool)),
                      settings->view, SLOT(setTabBarDoubleClkClose(bool)), Qt::DirectConnection );

    ui->checkDoubleClkNew->setChecked( settings->view->isTabBarDoubleClkNew() );
    connect( ui->checkDoubleClkNew, SIGNAL(toggled(bool)),
                      settings->view, SLOT(setTabBarDoubleClkNew(bool)), Qt::DirectConnection );

    ui->checkMiddleBtnClose->setChecked( settings->view->isTabBarMiddleBtnClose() );
    connect( ui->checkMiddleBtnClose, SIGNAL(toggled(bool)),
                      settings->view, SLOT(setTabBarMiddleBtnClose(bool)), Qt::DirectConnection );

    ui->checkMiddleBtnNew->setChecked( settings->view->isTabBarMiddleBtnNew() );
    connect( ui->checkMiddleBtnNew, SIGNAL(toggled(bool)),
                      settings->view, SLOT(setTabBarMiddleBtnNew(bool)), Qt::DirectConnection );

    ui->checkModernStyle->setChecked( settings->view->isTabBarModernStyleEnabled() );
    connect( ui->checkModernStyle, SIGNAL(toggled(bool)),
                      settings->view, SLOT(setTabBarModernStyleEnabled(bool)), Qt::DirectConnection );
}

PageView::~PageView()
{
    delete ui;
}

