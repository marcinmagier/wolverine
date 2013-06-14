#ifndef WDOCKFINDRES_H
#define WDOCKFINDRES_H

#include "qtdockwidget.h"



namespace Wolverine
{

class FindResWidget;

class DockFindRes : public QtDockWidget
{
    Q_OBJECT

public:
    explicit DockFindRes(QWidget *parent = 0);
    ~DockFindRes();
    
signals:
    
public slots:

protected:
    void changeVisibility(bool visible);


private:
    FindResWidget *mResWidget;
    
};

}

#endif // WDOCKFINDRES_H
