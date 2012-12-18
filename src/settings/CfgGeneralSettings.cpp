
#include "CfgGeneralSettings.h"

#include <QLocale>



GeneralSettings::GeneralSettings()
{
    mLanguage = QLocale::system().name();

    mLogLevel = "Info";
    mLogFilePath = "Wolverine.log";
    mLogFileEnabled = true;
    mLogConsoleEnabled = true;

    mTabBarHidden = false;
    mTabBarVertical = false;
    mTabBarLocked = false;
    mTabBarCloseVisible = true;
    mTabBarDoubleClkClose = true;
    mTabBarMiddleBtnClose = true;
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

void GeneralSettings::setTabBarHidden(bool val)
{
    if(mTabBarHidden != val) {
        mTabBarHidden = val;
        emit tabBarHiddenChanged(mTabBarHidden);
    }
}
bool GeneralSettings::isTabBarHidden()
{
    return mTabBarHidden;
}

void GeneralSettings::setTabBarVertical(bool val)
{
    if(mTabBarVertical != val) {
        mTabBarVertical = val;
        emit tabBarVerticalChanged(mTabBarVertical);
    }
}
bool GeneralSettings::isTabBarVertical()
{
    return mTabBarVertical;
}

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


