
#include "CfgAppSettings.h"
#include "CfgDynamicSettings.h"
#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
#include "CfgScintillaSettings.h"
#include "CfgStartupSettings.h"

#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>


#define W_CONFIG_FILE_NAME  "appconfig"

AppSettings* AppSettings::sAppConfig = 0;
AppSettings* AppSettings::sStartupConfig = 0;



AppSettings::AppSettings()
{
    mBackup = 0;

    dynamic = 0;
    general = 0;
    hidden = 0;
    scintilla = 0;
    startup = 0;
}

AppSettings::~AppSettings()
{
    if(dynamic)
        delete dynamic;
    if(general)
        delete general;
    if(hidden)
        delete hidden;
    if(scintilla)
        delete scintilla;
    if(startup)
        delete startup;
}

void AppSettings::initialize()
{
    dynamic = new DynamicSettings();
    general = new GeneralSettings();
    hidden = new HiddenSettings();
    scintilla = new ScintillaSettings();

    if(sStartupConfig) {
        // sStartup is no more needed
        startup = sStartupConfig->startup;
        sStartupConfig->startup = 0;
        delete sStartupConfig;
        sStartupConfig = 0;
    }
    else {
        startup = new StartupSettings();
    }

    loadConfiguration();
    qAddPostRoutine(deleteInstance);
}

void AppSettings::initializeStartup()
{
    startup = new StartupSettings();

    // Load only startup settings in order to speedup application startup
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), W_CONFIG_FILE_NAME);
    loadGroup(qset, startup);
}

//static
AppSettings* AppSettings::instance()
{
    if(sAppConfig == 0) {
        sAppConfig = new AppSettings();
        sAppConfig->initialize();
    }

    return sAppConfig;
}

//static
AppSettings* AppSettings::instanceStartup()
{
    if(sStartupConfig == 0) {
        sStartupConfig = new AppSettings();
        sStartupConfig->initializeStartup();
    }
    return sStartupConfig;
}

//static
void AppSettings::instanceWithNewThread()
{
    instance();
}

//static
void AppSettings::deleteInstance()
{
    if(sAppConfig) {
        sAppConfig->dropConfigurationBackup();
        sAppConfig->saveConfiguration();
        delete sAppConfig;
        sAppConfig = 0;
    }

    if(sStartupConfig) {
        delete sStartupConfig;
        sStartupConfig = 0;
    }

}


//virtual
bool AppSettings::loadConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), W_CONFIG_FILE_NAME);

    loadGroup(qset, general);
    loadGroup(qset, hidden);
    loadGroup(qset, scintilla);
    loadGroup(qset, startup);
	return true;
}

//virtual
bool AppSettings::saveConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), W_CONFIG_FILE_NAME);

    if (!qset.isWritable())
        return false;

    saveGroup(qset, general);
    saveGroup(qset, hidden);
    saveGroup(qset, scintilla);
    saveGroup(qset, startup);
	return true;
}

void AppSettings::copy(AppSettings *to, const AppSettings *from)
{
    copyGroup(to->dynamic,   from->dynamic);
    copyGroup(to->general,   from->general);
    copyGroup(to->hidden,    from->hidden);
    copyGroup(to->scintilla, from->scintilla);
    copyGroup(to->startup,   from->startup);
}


//virtual
void AppSettings::createConfigurationBackup()
{
    if(mBackup)
        delete mBackup;
    mBackup = new AppSettings();
    copy(mBackup, sAppConfig);
}


//virtual
void AppSettings::restoreConfigurationBackup()
{
    if(mBackup) {
        copy(sAppConfig, mBackup);
        delete mBackup;
        mBackup = 0;
    }
}


//virtual
void AppSettings::dropConfigurationBackup()
{
    if(mBackup) {
        delete mBackup;
        mBackup = 0;
    }
}


