#include "WFindResWidget.h"
#include "WFindResTab.h"
#include "WFinder.h"

#include "CfgAppSettings.h"
#include "CfgViewSettings.h"

#include <qttabbar.h>


using namespace Wolverine;

FindResWidget::FindResWidget(Finder *finder, QWidget *parent) :
    QtTabWidget(parent),
    mFinder(finder)
{
    mTabBar = new QtTabBar(this);
    this->setTabBar(mTabBar);
    this->setTabsClosable(true);

    AppSettings *settings = AppSettings::instance();
    connect( settings->view, SIGNAL(tabBarModernStyleEnabledChanged(bool)),
                       this, SLOT(onModernStyleEnabledChanged(bool)), Qt::DirectConnection);

    connect( this, SIGNAL(tabCloseRequested(int)),
             this, SLOT(onTabCloseRequested(int)) );

    onModernStyleEnabledChanged(settings->view->isTabBarModernStyleEnabled());
}

FindResWidget::~FindResWidget()
{

}


void FindResWidget::find(const FindRequest &req)
{
    WFindResTab *tab = new WFindResTab(req, mFinder->mCentralWidget, this);
    int idx = this->addTab(tab, req.searchPattern);
    this->setCurrentIndex(idx);
    tab->startSearching();
}



void FindResWidget::onModernStyleEnabledChanged(bool enabled)
{
    this->setModernStyleListButtonEnabled(enabled);
    if(enabled)
        mTabBar->setStyle(QtTabBar::MODERN);
    else
       mTabBar->setStyle(QtTabBar::CLASSIC);
}

void FindResWidget::onTabCloseRequested(int idx)
{
    QWidget *tab = this->widget(idx);
    this->removeTab(idx);
    delete tab;

    if(this->count() == 0)
        static_cast<QWidget*>(this->parent())->hide();
}
