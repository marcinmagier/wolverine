
#include "CfgStartupSettings.h"

#include <QLocale>



StartupSettings::StartupSettings()
{
    mLanguage = QLocale::system().name();

    mLogLevel = "Info";
    mLogFilePath = "Wolverine.log";
    mLogFileEnabled = true;
    mLogConsoleEnabled = true;
}


QString StartupSettings::getAppPath()
{
    return mAppPath;
}

QString StartupSettings::getLanguage()
{
    return mLanguage;
}

QString StartupSettings::getLogLevel()
{
    return mLogLevel;
}

QString StartupSettings::getLogFilePath()
{
    return mLogFilePath;
}

bool StartupSettings::isLogFileEnabled()
{
    return mLogFileEnabled;
}

bool StartupSettings::isLogConsoleEnabled()
{
    return mLogConsoleEnabled;
}




void StartupSettings::setAppPath(QString val)
{
    mAppPath = val;
}

void StartupSettings::setLanguage(QString val)
{
    if(mLanguage != val) {
        mLanguage = val;
        emit languageChanged(mLanguage);
    }
}

void StartupSettings::setLogLevel(QString val)
{
    mLogLevel = val;
}

void StartupSettings::setLogFilePath(QString val)
{
    mLogFilePath = val;
}

void StartupSettings::setLogFileEnabled(bool val)
{
    mLogFileEnabled = val;
}

void StartupSettings::setLogConsoleEnabled(bool val)
{
    mLogConsoleEnabled = val;
}


