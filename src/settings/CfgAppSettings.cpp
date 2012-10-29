
#include "CfgAppSettings.h"

#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>


CfgAppSettings* CfgAppSettings::s_appconfig = 0;

CfgAppSettings::CfgAppSettings()
{
    m_backup = 0;
}

CfgAppSettings::~CfgAppSettings()
{
    dropConfigurationBackup();
}

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
    if(m_backup)
        delete m_backup;
    m_backup = new CfgAppSettings();
    copy(m_backup, s_appconfig);
}

void CfgAppSettings::restoreConfigurationBackup()
{
    if(m_backup) {
        copy(s_appconfig, m_backup);
        delete m_backup;
        m_backup = 0;
    }
}

void CfgAppSettings::dropConfigurationBackup()
{
    if(m_backup) {
        delete m_backup;
        m_backup = 0;
    }
}
