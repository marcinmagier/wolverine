
#ifndef __CFG_STARTUP_SETTINGS_H_
 #define __CFG_STARTUP_SETTINGS_H_

#include <QObject>
#include <QString>

class StartupSettings : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QString	appPath                 READ getAppPath                 WRITE setAppPath            )

    Q_PROPERTY(QString	language                READ getLanguage                WRITE setLanguage           )

    Q_PROPERTY(QString	logLevel                READ getLogLevel                WRITE setLogLevel           )
    Q_PROPERTY(QString	logFilePath             READ getLogFilePath             WRITE setLogFilePath        )
    Q_PROPERTY(bool		logFileEnabled  		READ isLogFileEnabled   		WRITE setLogFileEnabled     )
    Q_PROPERTY(bool		logConsoleEnabled		READ isLogConsoleEnabled		WRITE setLogConsoleEnabled  )

    Q_PROPERTY(bool		alwaysNewInstance		READ isAlwaysNewInstance		WRITE setAlwaysNewInstance  )


public:
    explicit StartupSettings();

    QString getAppPath();

    QString getLanguage();

    QString getLogLevel();
    QString getLogFilePath();
    bool isLogFileEnabled();
    bool isLogConsoleEnabled();

    bool isAlwaysNewInstance();



signals:
    void languageChanged(QString val);


public slots:
    void setAppPath(QString val);

    void setLanguage(QString val);

    void setLogLevel(QString val);
    void setLogFilePath(QString val);
    void setLogFileEnabled(bool val);
    void setLogConsoleEnabled(bool val);

    void setAlwaysNewInstance(bool val);



private:
    QString mAppPath;

    QString mLanguage;

    QString mLogLevel;
    QString mLogFilePath;
    bool mLogFileEnabled;
    bool mLogConsoleEnabled;

    bool mAlwaysNewInstance;

};

#endif //__CFG_STARTUP_SETTINGS_H_
