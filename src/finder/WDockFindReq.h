#ifndef WDOCKFINDREQ_H
#define WDOCKFINDREQ_H

#include "qtdockwidget.h"


namespace Wolverine
{

class FindReqWidget;


class DockFindReq : public QtDockWidget
{
    Q_OBJECT

public:
    explicit DockFindReq(QWidget *parent = 0);
    ~DockFindReq();


signals:
    
public slots:

protected:
    virtual void changeVisibility(bool visible);


private:
    FindReqWidget *mReqWidget;
    
};


}

#endif // WDOCKFINDREQ_H
