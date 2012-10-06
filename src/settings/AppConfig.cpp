
#include "AppConfig.h"
#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>

AppConfig* AppConfig::s_appconfig = 0;

AppConfig* AppConfig::instance()
{
    if(s_appconfig == 0)
        s_appconfig = new AppConfig();
    return s_appconfig;
}

bool AppConfig::loadConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "appconfig");

    loadGroup(qset, &general);
    loadGroup(qset, &hidden);
    loadGroup(qset, &scintilla);
	return true;
}

bool AppConfig::saveConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "appconfig");

    if (!qset.isWritable())
        return false;

    saveGroup(qset, &general);
    saveGroup(qset, &hidden);
    saveGroup(qset, &scintilla);
	return true;
}
