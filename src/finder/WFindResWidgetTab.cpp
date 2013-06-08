#include "WFindResWidgetTab.h"


#include "Logger.h"

#include <QDebug>


using namespace Wolverine;

FindResWidgetTab::FindResWidgetTab(const FindRequest &req, QWidget *parent) :
    QTreeWidget(parent),
    mFindRequest(req)
{
    mProcess = 0;

    setHeaderHidden(true);
    search();
}

FindResWidgetTab::~FindResWidgetTab()
{
    killProc();
}


const FindRequest& FindResWidgetTab::getFindRequest()
{
    return mFindRequest;
}


void FindResWidgetTab::setTabIdx(int nr)
{
    mTabIdx = nr;
}

int FindResWidgetTab::getTabIdx()
{
    return mTabIdx;
}



void FindResWidgetTab::onProcReadyStandardOutput()
{

    while(mProcess->canReadLine()) {
        QByteArray line = mProcess->readLine();
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, line);
        this->addTopLevelItem(item);
    }


}

void FindResWidgetTab::onProcReadyStandardError()
{
    LOG_INFO( QString(mProcess->readAllStandardError()) );
}

void FindResWidgetTab::onProcFinished(int exitCode)
{
    emit searchProcFinished(mTabIdx);

    if(exitCode)
        LOG_ERROR("Search process finished with error code %d", exitCode);
}

void FindResWidgetTab::search()
{
    killProc();

    mProcess = new QProcess();
    connect( mProcess, SIGNAL(readyReadStandardOutput()),
                 this, SLOT(onProcReadyStandardOutput()) );
    connect( mProcess, SIGNAL(readyReadStandardError()),
                 this, SLOT(onProcReadyStandardError()) );
    connect( mProcess, SIGNAL(finished(int)),
                 this, SLOT(onProcFinished(int)) );

    mProcess->start("F:\\TMP\\grep.exe", QStringList() << "-rn" << "include" << "F:\\IT\\qt\\wolverine");
}

void FindResWidgetTab::killProc()
{
    if(mProcess) {
        if(mProcess->state() == QProcess::Running) {
            mProcess->kill();
            mProcess->waitForFinished(100);
        }
        delete mProcess;
        mProcess = 0;
    }
}
