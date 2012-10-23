
#include "CfgAppSettings.h"

#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>


CfgAppSettings* CfgAppSettings::s_appconfig = 0;
CfgAppSettings* CfgAppSettings::s_backup = 0;

CfgAppSettings* CfgAppSettings::instance()
{
    if(s_appconfig == 0) {
        s_appconfig = new CfgAppSettings();
        s_appconfig->loadConfiguration();
    }
    return s_appconfig;
}


bool CfgAppSettings::loadConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "appconfig");

    loadGroup(qset, &general);
    loadGroup(qset, &hidden);
    loadGroup(qset, &scintilla);
	return true;
}


bool CfgAppSettings::saveConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "appconfig");

    if (!qset.isWritable())
        return false;

    saveGroup(qset, &general);
    saveGroup(qset, &hidden);
    saveGroup(qset, &scintilla);
	return true;
}

void CfgAppSettings::copy(CfgAppSettings *to, const CfgAppSettings *from)
{
    copyGroup(&to->general,   &from->general);
    copyGroup(&to->hidden,    &from->hidden);
    copyGroup(&to->scintilla, &from->scintilla);
}


void CfgAppSettings::createConfigurationBackup()
{
    if(s_backup)
        delete s_backup;
    s_backup = new CfgAppSettings();
    copy(s_backup, s_appconfig);
}

void CfgAppSettings::restoreConfigurationBackup()
{
    copy(s_appconfig, s_backup);
    delete s_backup;
    s_backup = 0;
}

void CfgAppSettings::dropConfigurationBackup()
{
    delete s_backup;
    s_backup = 0;
}
