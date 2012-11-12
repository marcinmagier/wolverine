
#include "CfgGeneralSettings.h"

GeneralSettings::GeneralSettings()
{
    mLanguage = "";

    mLogLevel = "Info";
    mLogFilePath = "Wolverine.log";
    mLogFileEnabled = true;
    mLogConsoleEnabled = true;
}


void GeneralSettings::setLanguage(QString val)
{
    if(mLanguage != val) {
        mLanguage = val;
        emit languageChanged(mLanguage);
    }
}


void GeneralSettings::setLogLevel(QString val)
{
    mLogLevel = val;
}

void GeneralSettings::setLogFilePath(QString val)
{
    mLogFilePath = val;
}

void GeneralSettings::setLogFileEnabled(bool val)
{
    mLogFileEnabled = val;
}

void GeneralSettings::setLogConsoleEnabled(bool val)
{
    mLogConsoleEnabled = val;
}


