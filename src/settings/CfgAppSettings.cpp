
#include "CfgAppSettings.h"

#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>


static AppSettings* s_appconfig = 0;
const QString AppSettings::sConfigFileName = "appconfig";

static void cleanupAppSettings()
{
    delete s_appconfig;
    s_appconfig = 0;
}


AppSettings::AppSettings()
{
    mBackup = 0;

    dynamic = new DynamicSettings();
    general = new GeneralSettings();
    hidden = new HiddenSettings();
    scintilla = new ScintillaSettings();

    loadConfiguration();
    qAddPostRoutine(cleanupAppSettings);
}

AppSettings::~AppSettings()
{
    dropConfigurationBackup();
    saveConfiguration();

    delete general;
    delete hidden;
    delete scintilla;
}

AppSettings* AppSettings::instance()
{
    if(s_appconfig == 0)
        s_appconfig = new AppSettings();
    return s_appconfig;
}


bool AppSettings::loadConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), sConfigFileName);

    loadGroup(qset, general);
    loadGroup(qset, hidden);
    loadGroup(qset, scintilla);
	return true;
}


bool AppSettings::saveConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), sConfigFileName);

    if (!qset.isWritable())
        return false;

    saveGroup(qset, general);
    saveGroup(qset, hidden);
    saveGroup(qset, scintilla);
	return true;
}

void AppSettings::copy(AppSettings *to, const AppSettings *from)
{
    copyGroup(to->general,   from->general);
    copyGroup(to->hidden,    from->hidden);
    copyGroup(to->scintilla, from->scintilla);
}


void AppSettings::createConfigurationBackup()
{
    if(mBackup)
        delete mBackup;
    mBackup = new AppSettings();
    copy(mBackup, s_appconfig);
}

void AppSettings::restoreConfigurationBackup()
{
    if(mBackup) {
        copy(s_appconfig, mBackup);
        delete mBackup;
        mBackup = 0;
    }
}

void AppSettings::dropConfigurationBackup()
{
    if(mBackup) {
        delete mBackup;
        mBackup = 0;
    }
}

