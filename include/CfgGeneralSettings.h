
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
    Q_PROPERTY(bool     appBackupCopyEnabled        READ isAppBackupCopyEnabled         WRITE setAppBackupCopyEnabled       )



public:
    explicit GeneralSettings();

    bool isAppCloseWhenLastTabClosed();
    bool isAppCustomizeEnabled();
    bool isAppOpenFromCurrentEnabled();
    QString getAppLastOpenedDir();
    bool isAppBackupCopyEnabled();


signals:
    void appCloseWhenLastTabClosedChanged(bool val);
    void appCustomizeEnabledChanged(bool val);
    void appOpenFromCurrentChanged(bool val);
    void appLastOpenedDirChanged(QString val);
    void appBackupCopyEnabledChanged(bool val);


public slots:
    void setAppCloseWhenLastTabClosed(bool val);
    void setAppCustomizeEnabled(bool val);
    void setAppOpenFromCurrentEnabled(bool val);
    void setAppLastOpenedDir(const QString &val);
    void setAppBackupCopyEnabled(bool val);


private:
    bool mAppCloseWhenLastTabClosed;
    bool mAppCustomizeEnabled;
    bool mAppOpenFromCurrentEnabled;
    QString mAppLastOpenedDir;
    bool mAppBackupCopyEnabled;

};

#endif //__CFG_GENERAL_SETTINGS_H_
