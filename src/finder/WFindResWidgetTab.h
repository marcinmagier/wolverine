#ifndef WFINDRESWIDGETTAB_H
#define WFINDRESWIDGETTAB_H

#include "WFindRequest.h"

#include <QTreeWidget>
#include <QProcess>



namespace Wolverine
{


class FindResWidgetTab : public QTreeWidget
{
    Q_OBJECT

public:
    explicit FindResWidgetTab(const FindRequest &req, QWidget *parent = 0);
    ~FindResWidgetTab();
    
    const FindRequest& getFindRequest();

    void setTabIdx(int nr);
    int getTabIdx();

signals:
    void searchProcFinished(int nr);
    
public slots:


private slots:
    void onProcReadyStandardOutput();
    void onProcReadyStandardError();
    void onProcFinished(int exitCode);

private:
    void search();
    void killProc();


    QProcess *mProcess;
    FindRequest mFindRequest;
    int mTabIdx;
    
};


}

#endif // WFINDRESWIDGETTAB_H
