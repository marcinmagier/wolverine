
#include "CfgGeneralSettings.h"

GeneralSettings::GeneralSettings()
{
    m_logLevel = "Info";
    m_logConsoleEnabled = true;
    m_logFileEnabled = true;
}


void GeneralSettings::setLogLevel(QString val) {
    if(m_logLevel != val) {
        m_logLevel = val;
        emit logLevelChanged(val);
    }
}

void GeneralSettings::setLogConsoleEnabled(bool val) {
    if(m_logConsoleEnabled != val) {
        m_logConsoleEnabled = val;
        emit logConsoleEnabledChanged(val);
    }
}

void GeneralSettings::setLogFileEnabled(bool val) {
    if(m_logFileEnabled != val) {
        m_logFileEnabled = val;
        emit logFileEnabledChanged(val);
    }
}
