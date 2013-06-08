

#ifndef WFINDRESWIDGET_H
#define WFINDRESWIDGET_H

#include <qttabwidget.h>

#include "WFindRequest.h"

class QtTabBar;

namespace Wolverine
{

class Finder;

class FindResWidget : public QtTabWidget
{
    Q_OBJECT
    
public:
    explicit FindResWidget(Finder *finder, QWidget *parent = 0);
    ~FindResWidget();

    void find(const FindRequest &req);
    

private slots:
    void onModernStyleEnabledChanged(bool enabled);
    void onSearchProcFinished(int idx);

private:
    QtTabBar *mTabBar;
    Finder *mFinder;

};

}

#endif // WFINDRESWIDGET_H
