
#include "wolverine_cfg.h"

#include "PageGeneral.h"
#include "ui_PageGeneral.h"

#include "CfgAppSettings.h"
#include "CfgStartupSettings.h"
#include "CfgDynamicSettings.h"


using namespace Wolverine::Settings;

PageGeneral::PageGeneral(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageGeneral)
{

    ui->setupUi(this);

    ui->chboxSingleInstance->setChecked(settings->startup->isAlwaysNewInstance());
    connect( ui->chboxSingleInstance, SIGNAL(toggled(bool)),
                   settings->startup, SLOT(setAlwaysNewInstance(bool)), Qt::DirectConnection );


    mTranslations = settings->dynamic->getTranslations();
    foreach(QString lang, mTranslations) {
        ui->cmbLanguage->addItem(QLocale(lang).nativeLanguageName());
    }
    QString lang = QLocale(settings->startup->getLanguage()).nativeLanguageName();
    int idx = ui->cmbLanguage->findText(lang);
    ui->cmbLanguage->setCurrentIndex(idx);
    connect( ui->cmbLanguage, SIGNAL(currentIndexChanged(int)),
                        this, SLOT(currentLanguageChanged(int)) );


    ui->cmbLogLevel->addItems( QString("Trace Debug Info Warning Error Fatal").split(" ") );
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
}

PageGeneral::~PageGeneral()
{
    delete ui;
}

void PageGeneral::currentLanguageChanged(int index)
{
    AppSettings::instance()->startup->setLanguage(mTranslations[index]);
}
