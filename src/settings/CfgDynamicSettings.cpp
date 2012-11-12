
#include "CfgDynamicSettings.h"
#include "CfgAppSettings.h"
#include "Logger.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QSettings>


DynamicSettings::DynamicSettings()
{
    mInstalDir = qApp->applicationDirPath();

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), AppSettings::sConfigFileName);
    QFileInfo finfo(qset.fileName());
    mDataDir = finfo.absoluteDir().absolutePath();
}
