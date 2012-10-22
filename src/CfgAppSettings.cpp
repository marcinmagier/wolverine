
#include "CfgAppSettings.h"
#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>

CfgAppSettings* CfgAppSettings::s_appconfig = 0;

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
