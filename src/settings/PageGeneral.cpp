
#include "wolverine_cfg.h"

#include "PageGeneral.h"
#include "ui_PageGeneral.h"

#include "CfgAppSettings.h"
#include "CfgStartupSettings.h"


using namespace Wolverine::Settings;

PageGeneral::PageGeneral(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageGeneral)
{

    ui->setupUi(this);

    ui->chboxSingleInstance->setChecked(settings->startup->isAlwaysNewInstance());
    connect( ui->chboxSingleInstance, SIGNAL(toggled(bool)),
                   settings->startup, SLOT(setAlwaysNewInstance(bool)) );

    QStringList languages = QString(LANGUAGES_SUPPORTED).split(" ");
    foreach(QString lang, languages) {
        ui->cmbLanguage->addItem(QLocale(lang).nativeLanguageName());
    }

    QString lang = QLocale(settings->startup->getLanguage()).nativeLanguageName();
    int idx = ui->cmbLanguage->findText(lang);
    ui->cmbLanguage->setCurrentIndex(idx);
    connect(   ui->cmbLanguage, SIGNAL(currentIndexChanged(QString)),
             settings->startup, SLOT(setLanguage(QString)) );

    ui->chboxConsoleLog->setChecked(settings->startup->isLogConsoleEnabled());
    connect( ui->chboxConsoleLog, SIGNAL(toggled(bool)),
               settings->startup, SLOT(setLogConsoleEnabled(bool)) );

    ui->chboxFileLog->setChecked(settings->startup->isLogFileEnabled());
    connect(  ui->chboxFileLog, SIGNAL(toggled(bool)),
             settings->startup, SLOT(setLogFileEnabled(bool)) );
}

PageGeneral::~PageGeneral()
{
    delete ui;
}
