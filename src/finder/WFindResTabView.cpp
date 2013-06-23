#include "WFindResTabView.h"


using namespace Wolverine;

FindResTabView::FindResTabView(QWidget *parent) :
    QTreeView(parent)
{

}


void FindResTabView::spanFileNames()
{
    for(int i=0; i<model()->rowCount(); i++)
        setFirstColumnSpanned(i, QModelIndex(), true);
}
