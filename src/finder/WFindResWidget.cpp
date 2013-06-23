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

    onModernStyleEnabledChanged(settings->view->isTabBarModernStyleEnabled());
}

FindResWidget::~FindResWidget()
{

}


void FindResWidget::find(const FindRequest &req)
{
    WFindResTab *tab = new WFindResTab(req, mFinder->mCentralWidget, this);
    this->addTab(tab, req.searchPattern);
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
