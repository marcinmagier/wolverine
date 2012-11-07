
#include "CfgGeneralSettings.h"

GeneralSettings::GeneralSettings()
{
    m_logLevel = "Info";
    m_logFilePath = "Wolverine.log";
    m_logFileEnabled = true;
    m_logConsoleEnabled = true;
}


void GeneralSettings::setLogLevel(QString val) {
    if(m_logLevel != val)
        m_logLevel = val;
}

void GeneralSettings::setLogFilePath(QString val)
{
    if(m_logFilePath != val)
        m_logFilePath = val;
}

void GeneralSettings::setLogFileEnabled(bool val) {
    if(m_logFileEnabled != val)
        m_logFileEnabled = val;
}

void GeneralSettings::setLogConsoleEnabled(bool val) {
    if(m_logConsoleEnabled != val)
        m_logConsoleEnabled = val;
}


