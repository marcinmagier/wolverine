
#ifndef __CFG_GENERAL_SETTINGS_H_
 #define __CFG_GENERAL_SETTINGS_H_


#include <QObject>
#include <QString>
#include <QStringList>



class GeneralSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool         appCloseWhenLastTabClosed   READ isAppCloseWhenLastTabClosed    WRITE setAppCloseWhenLastTabClosed  )
    Q_PROPERTY(bool         appCustomizeEnabled         READ isAppCustomizeEnabled          WRITE setAppCustomizeEnabled        )
    Q_PROPERTY(bool         appOpenFromCurrent          READ isAppOpenFromCurrentEnabled    WRITE setAppOpenFromCurrentEnabled  )
    Q_PROPERTY(QString      appLastOpenedDir            READ getAppLastOpenedDir            WRITE setAppLastOpenedDir           )
    Q_PROPERTY(bool         appBackupCopyEnabled        READ isAppBackupCopyEnabled         WRITE setAppBackupCopyEnabled       )

    Q_PROPERTY(bool         synchVEnabled               READ isSynchVEnabled                WRITE setSynchVEnabled              )
    Q_PROPERTY(bool         synchHEnabled               READ isSynchHEnabled                WRITE setSynchHEnabled              )

    Q_PROPERTY(bool         findCaseSensitive           READ isFindCaseSensitiveSet         WRITE setFindCaseSensitive          )
    Q_PROPERTY(bool         findWholeWords              READ isFindWholeWordsSet            WRITE setFindWholeWords             )
    Q_PROPERTY(bool         findRegexp                  READ isFindRegexpSet                WRITE setFindRegexp                 )
    Q_PROPERTY(bool         findReverseDirection        READ isFindReverseDirectionSet      WRITE setFindReverseDirection       )
    Q_PROPERTY(bool         findWrap                    READ isFindWrapSet                  WRITE setFindWrap                   )
    Q_PROPERTY(bool         findInSelection             READ isFindInSelectionSet           WRITE setFindInSelection            )
    Q_PROPERTY(bool         findMark                    READ isFindMarkSet                  WRITE setFindMark                   )
    Q_PROPERTY(bool         findInSubDirs               READ isFindInSubDirsSet             WRITE setFindInSubDirs              )
    Q_PROPERTY(bool         findInHiddenDirs            READ isFindInHiddenDirsSet          WRITE setFindInHiddenDirs           )
    Q_PROPERTY(QStringList  findSearchPatterns          READ getFindSearchPatterns          WRITE setFindSearchPatterns         )
    Q_PROPERTY(QStringList  findReplacePatterns         READ getFindReplacePatterns         WRITE setFindReplacePatterns        )
    Q_PROPERTY(QStringList  findFilters                 READ getFindFilters                 WRITE setFindFilters                )
    Q_PROPERTY(QStringList  findDirectories             READ getFindDirectories             WRITE setFindDirectories            )


public:
    explicit GeneralSettings();

    bool isAppCloseWhenLastTabClosed();
    bool isAppCustomizeEnabled();
    bool isAppOpenFromCurrentEnabled();
    QString getAppLastOpenedDir();
    bool isAppBackupCopyEnabled();

    bool isSynchVEnabled();
    bool isSynchHEnabled();

    bool isFindCaseSensitiveSet();
    bool isFindWholeWordsSet();
    bool isFindRegexpSet();
    bool isFindReverseDirectionSet();
    bool isFindWrapSet();
    bool isFindInSelectionSet();
    bool isFindMarkSet();
    bool isFindInSubDirsSet();
    bool isFindInHiddenDirsSet();
    const QStringList& getFindSearchPatterns();
    const QString& getFindLastSearchPattern();
    const QStringList& getFindReplacePatterns();
    const QString& getFindLastReplacePattern();
    const QStringList& getFindFilters();
    const QString& getFindLastFilter();
    const QStringList& getFindDirectories();
    const QString& getFindLastDirectory();


signals:
    void appCloseWhenLastTabClosedChanged(bool val);
    void appCustomizeEnabledChanged(bool val);
    void appOpenFromCurrentChanged(bool val);
    void appLastOpenedDirChanged(QString val);
    void appBackupCopyEnabledChanged(bool val);

    void synchVEnabledChanged(bool val);
    void synchHEnabledChanged(bool val);

    void findCaseSensitiveChanged(bool val);
    void findWholeWordsChanged(bool val);
    void findRegexpChanged(bool val);
    void findReverseDirectionChanged(bool val);
    void findWrapChanged(bool val);
    void findInSelectionChanged(bool val);
    void findMarkChanged(bool val);
    void findInSubDirsChanged(bool val);
    void findInHiddenDirsChanged(bool val);


public slots:
    void setAppCloseWhenLastTabClosed(bool val);
    void setAppCustomizeEnabled(bool val);
    void setAppOpenFromCurrentEnabled(bool val);
    void setAppLastOpenedDir(const QString &val);
    void setAppBackupCopyEnabled(bool val);

    void setSynchVEnabled(bool val);
    void setSynchHEnabled(bool val);

    void setFindCaseSensitive(bool val);
    void setFindWholeWords(bool val);
    void setFindRegexp(bool val);
    void setFindReverseDirection(bool val);
    void setFindWrap(bool val);
    void setFindInSelection(bool val);
    void setFindMark(bool val);
    void setFindInSubDirs(bool val);
    void setFindInHiddenDirs(bool val);
    void setFindSearchPatterns(const QStringList &val);
    void addFindSearchPattern(const QString &val);
    void setFindReplacePatterns(const QStringList &val);
    void addFindReplacePattern(const QString &val);
    void setFindFilters(const QStringList &val);
    void addFindFilter(const QString &val);
    void setFindDirectories(const QStringList &val);
    void addFindDirectory(const QString &val);


private:
    bool mAppCloseWhenLastTabClosed;
    bool mAppCustomizeEnabled;
    bool mAppOpenFromCurrentEnabled;
    QString mAppLastOpenedDir;
    bool mAppBackupCopyEnabled;

    bool mSynchVEnabled;
    bool mSynchHEnabled;

    bool mFindCaseSensitive;
    bool mFindWholeWords;
    bool mFindRegexp;
    bool mFindReverseDirection;
    bool mFindWrap;
    bool mFindInSelection;
    bool mFindMark;
    bool mFindInSubDirs;
    bool mFindInHiddenDirs;

    static const int FIND_HISTORY_LEN = 10;

    QStringList mFindSearchPatterns;
    QStringList mFindReplacePatterns;
    QStringList mFindFilters;
    QStringList mFindDirectories;

};

#endif //__CFG_GENERAL_SETTINGS_H_
