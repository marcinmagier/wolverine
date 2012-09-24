
#include "AppConfig.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>

AppConfig* AppConfig::s_settings = NULL;

AppConfig* AppConfig::getInstance()
{
    if(s_settings == NULL)
        s_settings = new AppConfig();
    return s_settings;
}

bool AppConfig::loadConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, "wolverine", "wolverine");

    loadGroup(qset, &general);
    loadGroup(qset, &hidden);
    loadGroup(qset, &scintilla);
	return true;
}

bool AppConfig::saveConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, "wolverine", "wolverine");

    if (!qset.isWritable())
        return false;

    saveGroup(qset, &general);
    saveGroup(qset, &hidden);
    saveGroup(qset, &scintilla);
	return true;
}
