
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
