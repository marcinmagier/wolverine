
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

    // Init patterns history with empty strings
    mFindSearchPatterns.append(QString());
    mFindReplacePatterns.append(QString());
    mFindFilters.append(QString());
    mFindDirectories.append(QString());
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

void GeneralSettings::setFindSearchPatterns(const QStringList &val)
{
    mFindSearchPatterns = val;
}
void GeneralSettings::addFindSearchPattern(const QString &val)
{
    if(val.isEmpty())
        return;

    mFindSearchPatterns.removeAll(val);
    mFindSearchPatterns.prepend(val);
    while(mFindSearchPatterns.length() > FIND_HISTORY_LEN)
        mFindSearchPatterns.removeLast();
}
const QStringList& GeneralSettings::getFindSearchPatterns()
{
    return mFindSearchPatterns;
}
const QString& GeneralSettings::getFindLastSearchPattern()
{
    return mFindSearchPatterns.at(0);
}

void GeneralSettings::setFindReplacePatterns(const QStringList &val)
{
    mFindReplacePatterns = val;
}
void GeneralSettings::addFindReplacePattern(const QString &val)
{
    if(val.isEmpty())
        return;

    mFindReplacePatterns.removeAll(val);
    mFindReplacePatterns.prepend(val);
    while(mFindReplacePatterns.length() > FIND_HISTORY_LEN)
        mFindReplacePatterns.removeLast();
}
const QStringList& GeneralSettings::getFindReplacePatterns()
{
    return mFindReplacePatterns;
}
const QString& GeneralSettings::getFindLastReplacePattern()
{
    return mFindReplacePatterns.at(0);
}

void GeneralSettings::setFindFilters(const QStringList &val)
{
    mFindFilters = val;
}
void GeneralSettings::addFindFilter(const QString &val)
{
    if(val.isEmpty())
        return;

    mFindFilters.removeAll(val);
    mFindFilters.prepend(val);
    while(mFindFilters.length() > FIND_HISTORY_LEN)
        mFindFilters.removeLast();
}
const QStringList &GeneralSettings::getFindFilters()
{
    return mFindFilters;
}
const QString& GeneralSettings::getFindLastFilter()
{
    return mFindFilters.at(0);
}

void GeneralSettings::setFindDirectories(const QStringList &val)
{
    mFindDirectories = val;
}
void GeneralSettings::addFindDirectory(const QString &val)
{
    if(val.isEmpty())
        return;

    mFindDirectories.removeAll(val);
    mFindDirectories.prepend(val);
    while(mFindDirectories.length() > FIND_HISTORY_LEN)
        mFindDirectories.removeLast();
}
const QStringList &GeneralSettings::getFindDirectories()
{
    return mFindDirectories;
}
const QString& GeneralSettings::getFindLastDirectory()
{
    return mFindDirectories.at(0);
}
