
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

    mFindCaseSensitive = false;
    mFindWholeWords = false;
    mFindRegexp = false;
    mFindReverseDirection = false;
    mFindWrap = false;
    mFindInSelection = false;
    mFindMark = false;
    mFindInSubDirs = false;
    mFindInHiddenDirs = false;
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






//========================  Find  ===========================================//

void GeneralSettings::setFindCaseSensitive(bool val)
{
    if(mFindCaseSensitive != val) {
        mFindCaseSensitive = val;
        emit findCaseSensitiveChanged(mFindCaseSensitive);
    }
}
bool GeneralSettings::isFindCaseSensitiveSet()
{
    return mFindCaseSensitive;
}

void GeneralSettings::setFindWholeWords(bool val)
{
    if(mFindWholeWords != val) {
        mFindWholeWords = val;
        emit findWholeWordsChanged(mFindWholeWords);
    }
}
bool GeneralSettings::isFindWholeWordsSet()
{
    return mFindWholeWords;
}

void GeneralSettings::setFindRegexp(bool val)
{
    if(mFindRegexp != val) {
        mFindRegexp = val;
        emit findRegexpChanged(mFindRegexp);
    }
}
bool GeneralSettings::isFindRegexpSet()
{
    return mFindRegexp;
}

void GeneralSettings::setFindReverseDirection(bool val)
{
    if(mFindReverseDirection != val) {
        mFindReverseDirection = val;
        emit findReverseDirectionChanged(mFindReverseDirection);
    }
}
bool GeneralSettings::isFindReverseDirectionSet()
{
    return mFindReverseDirection;
}

void GeneralSettings::setFindWrap(bool val)
{
    if(mFindWrap != val) {
        mFindWrap = val;
        emit findWrapChanged(mFindWrap);
    }
}
bool GeneralSettings::isFindWrapSet()
{
    return mFindWrap;
}

void GeneralSettings::setFindInSelection(bool val)
{
    if(mFindInSelection != val) {
        mFindInSelection = val;
        emit findInSelectionChanged(mFindInSelection);
    }
}
bool GeneralSettings::isFindInSelectionSet()
{
    return mFindInSelection;
}

void GeneralSettings::setFindMark(bool val)
{
    if(mFindMark != val) {
        mFindMark = val;
        emit findMarkChanged(mFindMark);
    }
}
bool GeneralSettings::isFindMarkSet()
{
    return mFindMark;
}

void GeneralSettings::setFindInSubDirs(bool val)
{
    if(mFindInSubDirs != val) {
        mFindInSubDirs = val;
        emit findInSubDirsChanged(mFindInSubDirs);
    }
}
bool GeneralSettings::isFindInSubDirsSet()
{
    return mFindInSubDirs;
}

void GeneralSettings::setFindInHiddenDirs(bool val)
{
    if(mFindInHiddenDirs != val) {
        mFindInHiddenDirs = val;
        emit findInHiddenDirsChanged(mFindInHiddenDirs);
    }
}
bool GeneralSettings::isFindInHiddenDirsSet()
{
    return mFindInHiddenDirs;
}

