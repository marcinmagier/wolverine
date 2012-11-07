
#include "CfgAppSettings.h"

#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>


static AppSettings* s_appconfig = 0;

static void cleanupAppSettings()
{
    delete s_appconfig;
    s_appconfig = 0;
}


AppSettings::AppSettings()
{
    m_backup = 0;

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
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "appconfig");

    loadGroup(qset, general);
    loadGroup(qset, hidden);
    loadGroup(qset, scintilla);
	return true;
}


bool AppSettings::saveConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "appconfig");

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
    if(m_backup)
        delete m_backup;
    m_backup = new AppSettings();
    copy(m_backup, s_appconfig);
}

void AppSettings::restoreConfigurationBackup()
{
    if(m_backup) {
        copy(s_appconfig, m_backup);
        delete m_backup;
        m_backup = 0;
    }
}

void AppSettings::dropConfigurationBackup()
{
    if(m_backup) {
        delete m_backup;
        m_backup = 0;
    }
}
