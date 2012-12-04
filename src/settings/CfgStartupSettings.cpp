
#include "CfgStartupSettings.h"

#include <QLocale>



StartupSettings::StartupSettings()
{
    mLanguage = QLocale::system().name();

    mLogLevel = "Warning";
    mLogFilePath = "Wolverine.log";
    mLogFileEnabled = true;
    mLogConsoleEnabled = true;

    mAlwaysNewInstance = false;
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

bool StartupSettings::isAlwaysNewInstance()
{
    return mAlwaysNewInstance;
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

void StartupSettings::setAlwaysNewInstance(bool val)
{
    mAlwaysNewInstance = val;
}

