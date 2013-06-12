#ifndef WFINDRESTAB_H
#define WFINDRESTAB_H

#include "WFindRequest.h"


#include <QWidget>

class QProcess;
class QMutex;
class QTabWidget;

namespace Ui {
class WFindResTab;
}

namespace Wolverine
{

class FindResTabModel;


class WFindResTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit WFindResTab(const FindRequest &req, QWidget *parent = 0);
    ~WFindResTab();

    void startSearching();

private slots:
    void onTimerTimeout();
    void onProcReadyStandardOutput();
    void onProcReadyStandardError();
    void onProcFinished(int exitCode);

private:
    void killProc();
    void updateTabIcon(bool done = false);


    Ui::WFindResTab *ui;
    FindRequest mFindRequest;
    FindResTabModel *mModel;


    QTabWidget *mParent;
    QProcess *mProcess;
    QTimer *mTimer;
    QMutex *mMutex;
    QStringList mRawHits;

    int mIconIdx;
    int mHits;
    int mFiles;

};


}



#endif // WFINDRESTAB_H
