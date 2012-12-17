
#include "CfgStartupSettings.h"

#include <QLocale>
#include <QDir>
#include <QFileInfo>



StartupSettings::StartupSettings()
{
    mLanguage = QLocale::system().name();

    mLogLevel = "Warning";
    mLogFilePath = QFileInfo(QDir::temp(), "Wolverine.log").filePath();
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
    // Convert to lang_country pattern
    QString lang = QLocale(val).name();
    if(lang == "C")
        lang = "en_US";

    if(mLanguage != lang) {
        mLanguage = lang;
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

