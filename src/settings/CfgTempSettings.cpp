
#include "CfgTempSettings.h"
#include "CfgAppSettings.h"
#include "Logger.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QSettings>


TempSettings::TempSettings()
{
    mInstalDir = qApp->applicationDirPath();

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), AppSettings::sConfigFile);
    QFileInfo finfo(qset.fileName());
    mDataDir = finfo.absoluteDir().absolutePath();
}
