
#include "CfgGeneralSettings.h"

#include <QLocale>



GeneralSettings::GeneralSettings()
{
    mAppCloseWhenLastTabClosed = false;
    mAppCustomizeEnabled = false;
    mAppOpenFromCurrentEnabled = false;
    mAppLastOpenedDir = ".";
    mAppBackupCopyEnabled = true;

    mSynchVEnabled = false;
    mSynchHEnabled = false;
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

void GeneralSettings::setAppOpenFromCurrentEnabled(bool val)
{
    if(mAppOpenFromCurrentEnabled != val) {
        mAppOpenFromCurrentEnabled = val;
        emit appOpenFromCurrentChanged(mAppOpenFromCurrentEnabled);
    }
}
bool GeneralSettings::isAppOpenFromCurrentEnabled()
{
    return mAppOpenFromCurrentEnabled;
}

void GeneralSettings::setAppLastOpenedDir(const QString &val)
{
    if(mAppLastOpenedDir != val) {
        mAppLastOpenedDir = val;
        emit appLastOpenedDirChanged(mAppLastOpenedDir);
    }
}
QString GeneralSettings::getAppLastOpenedDir()
{
    return mAppLastOpenedDir;
}

void GeneralSettings::setAppBackupCopyEnabled(bool val)
{
    if(mAppBackupCopyEnabled != val) {
        mAppBackupCopyEnabled = val;
        emit appBackupCopyEnabledChanged(mAppBackupCopyEnabled);
    }
}
bool GeneralSettings::isAppBackupCopyEnabled()
{
    return mAppBackupCopyEnabled;
}





//========================  Misc  ===========================================//

void GeneralSettings::setSynchVEnabled(bool val)
{
    if(mSynchVEnabled != val) {
        mSynchVEnabled = val;
        emit synchVEnabledChanged(mSynchVEnabled);
    }
}
bool GeneralSettings::isSynchVEnabled()
{
    return mSynchVEnabled;
}

void GeneralSettings::setSynchHEnabled(bool val)
{
    if(mSynchHEnabled != val) {
        mSynchHEnabled = val;
        emit synchHEnabledChanged(mSynchHEnabled);
    }
}
bool GeneralSettings::isSynchHEnabled()
{
    return mSynchHEnabled;
}
