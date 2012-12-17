
#include "CfgDynamicSettings.h"
#include "Logger.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QSettings>


DynamicSettings::DynamicSettings()
{
    mInstalDir = qApp->applicationDirPath();

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "appconfig");
    QFileInfo finfo(qset.fileName());
    mDataDir = finfo.absoluteDir().absolutePath();
}


QString DynamicSettings::getPluginsDir()
{
    return QDir(getInstalDir()).absoluteFilePath("plugins");
}

QString DynamicSettings::getTempDir()
{
    return QDir::tempPath();
}

QString DynamicSettings::getTranslationsDir()
{
    return QDir(getInstalDir()).absoluteFilePath("translations");
}

QStringList DynamicSettings::getTranslations()
{
    QStringList languages;
    QStringList translations = QDir(getTranslationsDir()).entryList(QStringList("wolverine_*.qm"));

    foreach(QString lang, translations) {
        languages.append(lang.mid(10, 5)); //wolverine_en_US.qm
    }

    return languages;
}
