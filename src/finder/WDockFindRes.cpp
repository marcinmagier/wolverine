#include "WDockFindRes.h"
#include "WFinder.h"
#include "WFindResWidget.h"

#include "Logger.h"



using namespace Wolverine;



/**
 *  Constructor
 *
 * @param parent
 */
DockFindRes::DockFindRes(QWidget *parent) :
    QtDockWidget(tr("Find Results"), parent),
    mResWidget(0)
{

}


/**
 *  Destructor
 */
DockFindRes::~DockFindRes()
{
    if(mResWidget)
        delete mResWidget;
}


/**
 *  Creates/deletes internal widget when dock visibility is changing.
 *
 * @param visible
 */
//virtual
void DockFindRes::changeVisibility(bool visible)
{
    if(visible) {
        if(mResWidget == 0)
            mResWidget = new FindResWidget(Finder::instance(), this);
        else
            LOG_DEBUG("FindResWidget is not null");
        this->setWidget(mResWidget);
        QtDockWidget::changeVisibility(visible);
    } else {
        QtDockWidget::changeVisibility(visible);
        this->setWidget(0);
        if(mResWidget) {
            delete mResWidget;
            mResWidget = 0;
        } else {
            LOG_DEBUG("FindResWidget is null");
        }
    }
}
