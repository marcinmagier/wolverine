
#include "AppSettings.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>


bool AppSettings::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "host_test", "settings_test");

    readGroup(settings, &general);
    readGroup(settings, &hidden);
    readGroup(settings, &scintilla);
	return true;
}

bool AppSettings::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "host_test", "settings_test");

    if (!settings.isWritable())
        return false;

    writeGroup(settings, &general);
    writeGroup(settings, &hidden);
    writeGroup(settings, &scintilla);
	return true;
}
