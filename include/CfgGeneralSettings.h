
#ifndef __CFG_GENERAL_SETTINGS_H_
 #define __CFG_GENERAL_SETTINGS_H_

#include <QObject>
#include <QString>

class GeneralSettings : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QString	language                READ getLanguage                WRITE setLanguage           )

    Q_PROPERTY(QString	logLevel                READ getLogLevel                WRITE setLogLevel           )
    Q_PROPERTY(QString	logFilePath             READ getLogFilePath             WRITE setLogFilePath        )
    Q_PROPERTY(bool		logFileEnabled  		READ isLogFileEnabled   		WRITE setLogFileEnabled     )
    Q_PROPERTY(bool		logConsoleEnabled		READ isLogConsoleEnabled		WRITE setLogConsoleEnabled  )


public:
    explicit GeneralSettings();

    QString getLanguage() { return mLanguage; }

    QString getLogLevel() { return mLogLevel; }
    QString getLogFilePath() { return mLogFilePath; }
    bool isLogFileEnabled() { return mLogFileEnabled; }
    bool isLogConsoleEnabled() { return mLogConsoleEnabled; }



signals:
    void languageChanged(QString val);


public slots:
    void setLanguage(QString val);

    void setLogLevel(QString val);
    void setLogFilePath(QString val);
    void setLogFileEnabled(bool val);
    void setLogConsoleEnabled(bool val);



private:
    QString mLanguage;

    QString mLogLevel;
    QString mLogFilePath;
    bool mLogFileEnabled;
    bool mLogConsoleEnabled;

};

#endif //__CFG_GENERAL_SETTINGS_H_
