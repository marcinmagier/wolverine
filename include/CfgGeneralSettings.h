
#ifndef __CFG_GENERAL_SETTINGS_H_
 #define __CFG_GENERAL_SETTINGS_H_

#include <QObject>
#include <QString>

class GeneralSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString  language                READ getLanguage                WRITE setLanguage               )

    Q_PROPERTY(QString  logLevel                READ getLogLevel                WRITE setLogLevel               )
    Q_PROPERTY(QString  logFilePath             READ getLogFilePath             WRITE setLogFilePath            )
    Q_PROPERTY(bool     logFileEnabled          READ isLogFileEnabled           WRITE setLogFileEnabled         )
    Q_PROPERTY(bool     logConsoleEnabled       READ isLogConsoleEnabled        WRITE setLogConsoleEnabled      )

    Q_PROPERTY(bool     tabBarHidden            READ isTabBarHidden             WRITE setTabBarHidden           )
    Q_PROPERTY(bool     tabBarVertical          READ isTabBarVertical           WRITE setTabBarVertical         )
    Q_PROPERTY(bool     tabBarLocked            READ isTabBarLocked             WRITE setTabBarLocked           )
    Q_PROPERTY(bool     tabBarCloseVisible      READ isTabBarCloseVisible       WRITE setTabBarCloseVisible     )
    Q_PROPERTY(bool     tabBarDoubleClkClose    READ isTabBarDoubleClkClose     WRITE setTabBarDoubleClkClose   )
    Q_PROPERTY(bool     tabBarMiddleBtnClose    READ isTabBarMiddleBtnClose     WRITE setTabBarMiddleBtnClose   )


public:
    explicit GeneralSettings();


    QString getLanguage();

    QString getLogLevel();
    QString getLogFilePath();
    bool isLogFileEnabled();
    bool isLogConsoleEnabled();

    bool isTabBarHidden();
    bool isTabBarVertical();
    bool isTabBarLocked();
    bool isTabBarCloseVisible();
    bool isTabBarDoubleClkClose();
    bool isTabBarMiddleBtnClose();


signals:
    void languageChanged(QString val);

    void tabBarHiddenChanged(bool val);
    void tabBarVerticalChanged(bool val);
    void tabBarLockedChanged(bool val);
    void tabBarCloseVisibleChanged(bool val);
    void tabBarDoubleClkCloseChanged(bool val);
    void tabBarMiddleBtnCloseChanged(bool val);


public slots:
    void setLanguage(QString val);

    void setLogLevel(QString val);
    void setLogFilePath(QString val);
    void setLogFileEnabled(bool val);
    void setLogConsoleEnabled(bool val);

    void setTabBarHidden(bool val);
    void setTabBarVertical(bool val);
    void setTabBarLocked(bool val);
    void setTabBarCloseVisible(bool val);
    void setTabBarDoubleClkClose(bool val);
    void setTabBarMiddleBtnClose(bool val);


private:
    QString mLanguage;

    QString mLogLevel;
    QString mLogFilePath;
    bool mLogFileEnabled;
    bool mLogConsoleEnabled;

    bool mTabBarHidden;
    bool mTabBarVertical;
    bool mTabBarLocked;
    bool mTabBarCloseVisible;
    bool mTabBarDoubleClkClose;
    bool mTabBarMiddleBtnClose;

};

#endif //__CFG_GENERAL_SETTINGS_H_
