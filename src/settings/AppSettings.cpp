
#include "AppSettings.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>

AppSettings* AppSettings::s_settings = NULL;

AppSettings* AppSettings::getInstance()
{
    if(s_settings == NULL)
        s_settings = new AppSettings();
    return s_settings;
}

bool AppSettings::readSettings()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, "wolverine", "wolverine");

    readGroup(qset, &general);
    readGroup(qset, &hidden);
    readGroup(qset, &scintilla);
	return true;
}

bool AppSettings::writeSettings()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, "wolverine", "wolverine");

    if (!qset.isWritable())
        return false;

    writeGroup(qset, &general);
    writeGroup(qset, &hidden);
    writeGroup(qset, &scintilla);
	return true;
}
