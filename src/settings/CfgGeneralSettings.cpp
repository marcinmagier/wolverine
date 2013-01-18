
#include "CfgGeneralSettings.h"

#include <QLocale>



GeneralSettings::GeneralSettings()
{
    mAppCloseWhenLastTabClosed = false;
    mAppCustomizeEnabled = false;

    mTabBarLocked = false;
    mTabBarCloseVisible = true;
    mTabBarDoubleClkClose = true;
    mTabBarDoubleClkNew = true;
    mTabBarMiddleBtnClose = true;
    mTabBarMiddleBtnNew = true;
    mTabBarIconVisible = true;
    mTabBarModernStyleEnabled = true;
}



//========================  App  ============================================//

void GeneralSettings::setAppCloseWhenLastTabClosed(bool val)
{
    if(mAppCloseWhenLastTabClosed != val) {
        mAppCloseWhenLastTabClosed = val;
        emit appCloseWhenLastTabClosedChanged(mAppCloseWhenLastTabClosed);
    }
}
bool GeneralSettings::isAppCloseWhenLastTabClosed()
{
    return mAppCloseWhenLastTabClosed;
}

void GeneralSettings::setAppCustomizeEnabled(bool val)
{
    if(mAppCustomizeEnabled != val) {
        mAppCustomizeEnabled = val;
        emit appCustomizeEnabledChanged(mAppCustomizeEnabled);
    }
}
bool GeneralSettings::isAppCustomizeEnabled()
{
    return mAppCustomizeEnabled;
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

