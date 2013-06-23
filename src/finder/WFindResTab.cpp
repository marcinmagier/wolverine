#include "WFindResTab.h"
#include "ui_WFindResTab.h"

#include "WFindResTabModel.h"

#include "WCentralWidget.h"
#include "WLib.h"

#include "Logger.h"

#include <QTimer>
#include <QProcess>
#include <QMutex>


using namespace Wolverine;

WFindResTab::WFindResTab(const FindRequest &req, CentralWidget *cw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WFindResTab),
    mFindRequest(req),
    mCentralWidget(cw),
    mProcess(0), mTimer(0),
    mIconIdx(0), mHits(0), mFiles(0)
{
    mParent = dynamic_cast<QTabWidget*>(parent);
    ui->setupUi(this);

    mModel = new FindResTabModel();
    ui->treeView->setModel(mModel);

    connect( ui->treeView, SIGNAL(doubleClicked(QModelIndex)),
                    this , SLOT(onFileNameDoubleClicked(QModelIndex)) );

}

WFindResTab::~WFindResTab()
{
    killProc();
    delete ui;
}


void WFindResTab::startSearching()
{
    this->updateTabIcon();

    killProc();

    mProcess = new QProcess();
    mProcess->setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    connect( mProcess, SIGNAL(readyReadStandardOutput()),
                 this, SLOT(onProcReadyStandardOutput()) );
    connect( mProcess, SIGNAL(readyReadStandardError()),
                 this, SLOT(onProcReadyStandardError()) );
    connect( mProcess, SIGNAL(finished(int)),
                 this, SLOT(onProcFinished(int)) );

    mTimer = new QTimer(this);
    connect( mTimer, SIGNAL(timeout()),
               this, SLOT(onTimerTimeout()) );

    mMutex = new QMutex();

    mTimer->start(400);

    QStringList args;
    args << "-rn";
    args << "--binary-files=without-match";
    args << mFindRequest.searchPattern;
    args << mFindRequest.directory;

    mProcess->start("grep.exe", args);
}



void WFindResTab::onTimerTimeout()
{
    updateTabIcon();

    mMutex->lock();
    mModel->addHits(mRawHits);
    mRawHits.clear();
    ui->lblHitNr->setText(QString("%1").arg(mModel->getHits()));
    ui->lblFilesNr->setText(QString("%1").arg(mModel->getFiles()));

    ui->treeView->spanFileNames();

    mMutex->unlock();

}

void WFindResTab::onProcFinished(int exitCode)
{
    mTimer->stop();
    delete mTimer;
    mTimer = 0;

    onTimerTimeout();
    updateTabIcon(true);


   // mModel->showHits();

    if(exitCode)
            LOG_ERROR("Search process finished with error code %d", exitCode);
}

void WFindResTab::onProcReadyStandardOutput()
{
    mMutex->lock();
    while(mProcess->canReadLine()) {
        QByteArray line = mProcess->readLine();
        mRawHits.append(QString(line).trimmed());
    }
    mMutex->unlock();
}

void WFindResTab::onProcReadyStandardError()
{
    LOG_ERROR( QString(mProcess->readAllStandardError()) );
}


void WFindResTab::onFileNameDoubleClicked(const QModelIndex &index)
{
    if(!index.parent().isValid())
        return;

    mCentralWidget->openTab(Lib::createFileName(mModel->getFileName(index), mModel->getLine(index)));

}


void WFindResTab::killProc()
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

void WFindResTab::updateTabIcon(bool done)
{
    int idx = mParent->indexOf(this);

    if(done) {
        mParent->setTabIcon(idx, QIcon(QString(":/search_done")) );
    } else {
        QString icon = QString(":/search_progress_%1.png").arg(mIconIdx);
        mParent->setTabIcon(idx, QIcon(icon));
        mIconIdx++;
        mIconIdx = (mIconIdx & 0x3);
    }


}




