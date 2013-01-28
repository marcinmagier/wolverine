
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




//=======================  Lang  ============================================//

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
QString StartupSettings::getLanguage()
{
    return mLanguage;
}




//=======================  Log  =============================================//

void StartupSettings::setLogLevel(QString val)
{
    mLogLevel = val;
}
QString StartupSettings::getLogLevel()
{
    return mLogLevel;
}

void StartupSettings::setLogFilePath(QString val)
{
    mLogFilePath = val;
}
QString StartupSettings::getLogFilePath()
{
    return mLogFilePath;
}

void StartupSettings::setLogFileEnabled(bool val)
{
    mLogFileEnabled = val;
}
bool StartupSettings::isLogFileEnabled()
{
    return mLogFileEnabled;
}

void StartupSettings::setLogConsoleEnabled(bool val)
{
    mLogConsoleEnabled = val;
}
bool StartupSettings::isLogConsoleEnabled()
{
    return mLogConsoleEnabled;
}

void StartupSettings::setAlwaysNewInstance(bool val)
{
    mAlwaysNewInstance = val;
}
bool StartupSettings::isAlwaysNewInstance()
{
    return mAlwaysNewInstance;
}




