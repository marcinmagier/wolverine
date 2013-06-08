#include "WFindResWidget.h"
#include "WFindResWidgetTab.h"

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
    FindResWidgetTab *tab = new FindResWidgetTab(req);
    int idx = this->addTab(tab, QIcon(":/search_progress.png"), req.searchPattern);
    tab->setTabIdx(idx);

    connect(  tab, SIGNAL(searchProcFinished(int)),
             this, SLOT(onSearchProcFinished(int)) );
}



void FindResWidget::onModernStyleEnabledChanged(bool enabled)
{
    this->setModernStyleListButtonEnabled(enabled);
    if(enabled)
        mTabBar->setStyle(QtTabBar::MODERN);
    else
       mTabBar->setStyle(QtTabBar::CLASSIC);
}


void FindResWidget::onSearchProcFinished(int idx)
{
    this->setTabIcon(idx, QIcon(":/search_done.png"));
}
