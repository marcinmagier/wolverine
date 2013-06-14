#include "WDockFindReq.h"
#include "WFinder.h"
#include "WFindReqWidget.h"


#include "Logger.h"

using namespace Wolverine;



/**
 *  Constructor
 *
 * @param parent
 */
DockFindReq::DockFindReq(QWidget *parent) :
    QtDockWidget(tr("Find"), parent),
    mReqWidget(0)
{

}


/**
 *  Destructor
 */
DockFindReq::~DockFindReq()
{
    if(mReqWidget)
        delete mReqWidget;
}


/**
 *  Creates/deletes internal widget when dock visibility is changing.
 *
 * @param visible
 */
//virtual
void DockFindReq::changeVisibility(bool visible)
{
    if(visible) {
        if(mReqWidget == 0)
            mReqWidget = new FindReqWidget(Finder::instance(), this);
        else
            LOG_DEBUG("FindReqWidget is not null");
        this->setWidget(mReqWidget);
        QtDockWidget::changeVisibility(visible);

    } else {
        QtDockWidget::changeVisibility(visible);
        this->setWidget(0);
        if(mReqWidget) {
            delete mReqWidget;
            mReqWidget = 0;
        } else {
            LOG_DEBUG("FindReqWidget is null");
        }
    }

}
