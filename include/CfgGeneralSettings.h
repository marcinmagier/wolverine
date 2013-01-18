
#ifndef __CFG_GENERAL_SETTINGS_H_
 #define __CFG_GENERAL_SETTINGS_H_


#include <QObject>
#include <QString>



class GeneralSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool     appCloseWhenLastTabClosed   READ isAppCloseWhenLastTabClosed    WRITE setAppCloseWhenLastTabClosed  )
    Q_PROPERTY(bool     appCustomizeEnabled         READ isAppCustomizeEnabled          WRITE setAppCustomizeEnabled        )
    Q_PROPERTY(bool     appOpenFromCurrent          READ isAppOpenFromCurrentEnabled    WRITE setAppOpenFromCurrentEnabled  )
    Q_PROPERTY(QString  appLastOpenedDir            READ getAppLastOpenedDir            WRITE setAppLastOpenedDir           )


    Q_PROPERTY(bool     tabBarLocked                READ isTabBarLocked                 WRITE setTabBarLocked               )
    Q_PROPERTY(bool     tabBarCloseVisible          READ isTabBarCloseVisible           WRITE setTabBarCloseVisible         )
    Q_PROPERTY(bool     tabBarDoubleClkClose        READ isTabBarDoubleClkClose         WRITE setTabBarDoubleClkClose       )
    Q_PROPERTY(bool     tabBarDoubleClkNew          READ isTabBarDoubleClkNew           WRITE setTabBarDoubleClkNew         )
    Q_PROPERTY(bool     tabBarMiddleBtnClose        READ isTabBarMiddleBtnClose         WRITE setTabBarMiddleBtnClose       )
    Q_PROPERTY(bool     tabBarMiddleBtnNew          READ isTabBarMiddleBtnNew           WRITE setTabBarMiddleBtnNew         )
    Q_PROPERTY(bool     tabBarIconVisible           READ isTabBarIconVisible            WRITE setTabBarIconVisible          )
    Q_PROPERTY(bool     tabBarModernStyleEnabled    READ isTabBarModernStyleEnabled     WRITE setTabBarModernStyleEnabled   )


public:
    explicit GeneralSettings();

    bool isAppCloseWhenLastTabClosed();
    bool isAppCustomizeEnabled();
    bool isAppOpenFromCurrentEnabled();
    QString getAppLastOpenedDir();

    bool isTabBarLocked();
    bool isTabBarCloseVisible();
    bool isTabBarDoubleClkClose();
    bool isTabBarDoubleClkNew();
    bool isTabBarMiddleBtnClose();
    bool isTabBarMiddleBtnNew();
    bool isTabBarIconVisible();
    bool isTabBarModernStyleEnabled();


signals:
    void appCloseWhenLastTabClosedChanged(bool val);
    void appCustomizeEnabledChanged(bool val);
    void appOpenFromCurrentChanged(bool val);
    void appLastOpenedDirChanged(QString val);

    void tabBarLockedChanged(bool val);
    void tabBarCloseVisibleChanged(bool val);
    void tabBarDoubleClkCloseChanged(bool val);
    void tabBarDoubleClkCloseNew(bool val);
    void tabBarMiddleBtnCloseChanged(bool val);
    void tabBarMiddleBtnCloseNew(bool val);
    void tabBarIconVisibleChanged(bool val);
    void tabBarModernStyleEnabledChanged(bool val);


public slots:
    void setAppCloseWhenLastTabClosed(bool val);
    void setAppCustomizeEnabled(bool val);
    void setAppOpenFromCurrentEnabled(bool val);
    void setAppLastOpenedDir(const QString &val);

    void setTabBarLocked(bool val);
    void setTabBarCloseVisible(bool val);
    void setTabBarDoubleClkClose(bool val);
    void setTabBarDoubleClkNew(bool val);
    void setTabBarMiddleBtnClose(bool val);
    void setTabBarMiddleBtnNew(bool val);
    void setTabBarIconVisible(bool val);
    void setTabBarModernStyleEnabled(bool val);


private:
    bool mAppCloseWhenLastTabClosed;
    bool mAppCustomizeEnabled;
    bool mAppOpenFromCurrentEnabled;
    QString mAppLastOpenedDir;

    bool mTabBarLocked;
    bool mTabBarCloseVisible;
    bool mTabBarDoubleClkClose;
    bool mTabBarDoubleClkNew;
    bool mTabBarMiddleBtnClose;
    bool mTabBarMiddleBtnNew;
    bool mTabBarIconVisible;
    bool mTabBarModernStyleEnabled;

};

#endif //__CFG_GENERAL_SETTINGS_H_
