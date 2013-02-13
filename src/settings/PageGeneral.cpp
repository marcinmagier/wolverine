
#include "wolverine_cfg.h"

#include "PageGeneral.h"
#include "ui_PageGeneral.h"

#include "CfgAppSettings.h"
#include "CfgStartupSettings.h"
#include "CfgDynamicSettings.h"
#include "CfgGeneralSettings.h"

#include <QFileInfo>
#include <QFileDialog>


using namespace Wolverine::Settings;

PageGeneral::PageGeneral(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageGeneral)
{

    ui->setupUi(this);

    ui->chboxSingleInstance->setChecked(settings->startup->isAlwaysNewInstance());
    connect( ui->chboxSingleInstance, SIGNAL(toggled(bool)),
                   settings->startup, SLOT(setAlwaysNewInstance(bool)), Qt::DirectConnection );

    ui->checkOpenFromCurrent->setChecked( settings->general->isAppOpenFromCurrentEnabled() );
    connect (ui->checkOpenFromCurrent, SIGNAL(toggled(bool)),
                    settings->general, SLOT(setAppOpenFromCurrentEnabled(bool)), Qt::DirectConnection );

    ui->checkBackupVer->setChecked( settings->general->isAppBackupCopyEnabled() );
    connect( ui->checkBackupVer, SIGNAL(toggled(bool)),
              settings->general, SLOT(setAppBackupCopyEnabled(bool)), Qt::DirectConnection );

    ui->checkCloseWhenLastClosed->setChecked( settings->general->isAppCloseWhenLastTabClosed() );
    connect( ui->checkCloseWhenLastClosed, SIGNAL(toggled(bool)),
                        settings->general, SLOT(setAppCloseWhenLastTabClosed(bool)), Qt::DirectConnection );


    mTranslations = settings->dynamic->getTranslations();
    foreach(QString lang, mTranslations) {
        ui->cmbLanguage->addItem(QLocale(lang).nativeLanguageName());
    }
    QString lang = QLocale(settings->startup->getLanguage()).nativeLanguageName();
    int idx = ui->cmbLanguage->findText(lang);
    ui->cmbLanguage->setCurrentIndex(idx);
    //ui->cmbLanguage is connected automatically


    ui->cmbLogLevel->addItems( QString(LOG_LEVELS).split(" ") );
    idx = ui->cmbLogLevel->findText(settings->startup->getLogLevel());
    ui->cmbLogLevel->setCurrentIndex(idx);
    connect(   ui->cmbLogLevel, SIGNAL(currentIndexChanged(QString)),
             settings->startup, SLOT(setLogLevel(QString)), Qt::DirectConnection );

    ui->chboxConsoleLog->setChecked(settings->startup->isLogConsoleEnabled());
    connect( ui->chboxConsoleLog, SIGNAL(toggled(bool)),
               settings->startup, SLOT(setLogConsoleEnabled(bool)), Qt::DirectConnection );

    ui->chboxFileLog->setChecked(settings->startup->isLogFileEnabled());
    connect(  ui->chboxFileLog, SIGNAL(toggled(bool)),
             settings->startup, SLOT(setLogFileEnabled(bool)), Qt::DirectConnection );

    ui->editLogFilePath->setText(settings->startup->getLogFilePath());
    ui->editLogFilePath->setEnabled(settings->startup->isLogFileEnabled());
    connect(    ui->chboxFileLog, SIGNAL(toggled(bool)),
             ui->editLogFilePath, SLOT(setEnabled(bool)) );

    //ui->btnLogFilePathDlg is connected automatically
    ui->btnLogFilePathDlg->setEnabled(settings->startup->isLogFileEnabled());
    connect(      ui->chboxFileLog, SIGNAL(toggled(bool)),
             ui->btnLogFilePathDlg, SLOT(setEnabled(bool)) );

    ui->lblLogFilePath->setEnabled(settings->startup->isLogFileEnabled());
    connect(   ui->chboxFileLog, SIGNAL(toggled(bool)),
             ui->lblLogFilePath, SLOT(setEnabled(bool)) );

}

PageGeneral::~PageGeneral()
{
    delete ui;
}

void PageGeneral::on_cmbLanguage_currentIndexChanged(int index)
{
    AppSettings::instance()->startup->setLanguage(mTranslations[index]);
}

void Wolverine::Settings::PageGeneral::on_btnLogFilePathDlg_clicked()
{
    QString logFile = ui->editLogFilePath->text();
    logFile = QFileDialog::getOpenFileName(this,
                                           tr("Open log file"),
                                           QFileInfo(logFile).absoluteDir().path() );
    if(!logFile.isEmpty())
        ui->editLogFilePath->setText(logFile);
}
