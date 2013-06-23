#ifndef WFINDRESTABVIEW_H
#define WFINDRESTABVIEW_H

#include <QTreeView>


namespace Wolverine {


class FindResTabView : public QTreeView
{
    Q_OBJECT

public:
    explicit FindResTabView(QWidget *parent = 0);

    void spanFileNames();

signals:
    
public slots:

private slots:
    
};


}

#endif // WFINDRESTABVIEW_H
