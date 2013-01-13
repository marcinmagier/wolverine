
#include "CfgGeneralSettings.h"

#include <QLocale>



GeneralSettings::GeneralSettings()
{
    mLanguage = QLocale::system().name();

    mLogLevel = "Info";
    mLogFilePath = "Wolverine.log";
    mLogFileEnabled = true;
    mLogConsoleEnabled = true;

    mTabBarLocked = false;
    mTabBarCloseVisible = true;
    mTabBarDoubleClkClose = true;
    mTabBarDoubleClkNew = true;
    mTabBarMiddleBtnClose = true;
    mTabBarMiddleBtnNew = true;
    mTabBarIconVisible = true;
    mTabBarModernStyleEnabled = true;
}


//=======================  Lang  ============================================//

void GeneralSettings::setLanguage(QString val)
{
    if(mLanguage != val) {
        mLanguage = val;
        emit languageChanged(mLanguage);
    }
}
QString GeneralSettings::getLanguage()
{
    return mLanguage;
}



//=======================  Log  =============================================//

void GeneralSettings::setLogLevel(QString val)
{
    mLogLevel = val;
}
QString GeneralSettings::getLogLevel()
{
    return mLogLevel;
}

void GeneralSettings::setLogFilePath(QString val)
{
    mLogFilePath = val;
}
QString GeneralSettings::getLogFilePath()
{
    return mLogFilePath;
}

void GeneralSettings::setLogFileEnabled(bool val)
{
    mLogFileEnabled = val;
}
bool GeneralSettings::isLogFileEnabled()
{
    return mLogFileEnabled;
}

void GeneralSettings::setLogConsoleEnabled(bool val)
{
    mLogConsoleEnabled = val;
}
bool GeneralSettings::isLogConsoleEnabled()
{
    return mLogConsoleEnabled;
}



//=======================  TabBar  ==========================================//

void GeneralSettings::setTabBarLocked(bool val)
{
    if(mTabBarLocked != val) {
        mTabBarLocked = val;
        emit tabBarLockedChanged(mTabBarLocked);
    }
}
bool GeneralSettings::isTabBarLocked()
{
    return mTabBarLocked;
}

void GeneralSettings::setTabBarCloseVisible(bool val)
{
    if(mTabBarCloseVisible != val) {
        mTabBarCloseVisible = val;
        emit tabBarCloseVisibleChanged(mTabBarCloseVisible);
    }
}
bool GeneralSettings::isTabBarCloseVisible()
{
    return mTabBarCloseVisible;
}

void GeneralSettings::setTabBarDoubleClkClose(bool val)
{
    if(mTabBarDoubleClkClose != val) {
        mTabBarDoubleClkClose = val;
        emit tabBarDoubleClkCloseChanged(mTabBarDoubleClkClose);
    }
}
bool GeneralSettings::isTabBarDoubleClkClose()
{
    return mTabBarDoubleClkClose;
}

void GeneralSettings::setTabBarDoubleClkNew(bool val)
{
    if(mTabBarDoubleClkNew != val) {
        mTabBarDoubleClkNew = val;
        emit tabBarDoubleClkCloseChanged(mTabBarDoubleClkNew);
    }
}
bool GeneralSettings::isTabBarDoubleClkNew()
{
    return mTabBarDoubleClkNew;
}

void GeneralSettings::setTabBarMiddleBtnClose(bool val)
{
    if(mTabBarMiddleBtnClose != val) {
        mTabBarMiddleBtnClose = val;
        emit tabBarMiddleBtnCloseChanged(mTabBarMiddleBtnClose);
    }
}
bool GeneralSettings::isTabBarMiddleBtnClose()
{
    return mTabBarMiddleBtnClose;
}

void GeneralSettings::setTabBarMiddleBtnNew(bool val)
{
    if(mTabBarMiddleBtnNew != val) {
        mTabBarMiddleBtnNew = val;
        emit tabBarMiddleBtnCloseChanged(mTabBarMiddleBtnNew);
    }
}
bool GeneralSettings::isTabBarMiddleBtnNew()
{
    return mTabBarMiddleBtnNew;
}

void GeneralSettings::setTabBarIconVisible(bool val)
{
    if(mTabBarIconVisible != val) {
        mTabBarIconVisible = val;
        emit tabBarIconVisibleChanged(mTabBarIconVisible);
    }
}
bool GeneralSettings::isTabBarIconVisible()
{
    return mTabBarIconVisible;
}

void GeneralSettings::setTabBarModernStyleEnabled(bool val)
{
    if(mTabBarModernStyleEnabled != val) {
        mTabBarModernStyleEnabled = val;
        emit tabBarModernStyleEnabledChanged(mTabBarModernStyleEnabled);
    }
}
bool GeneralSettings::isTabBarModernStyleEnabled()
{
    return mTabBarModernStyleEnabled;
}

