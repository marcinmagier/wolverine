
#ifndef __CFG_GENERAL_SETTINGS_H_
 #define __CFG_GENERAL_SETTINGS_H_

#include <QObject>
#include <QString>

class GeneralSettings : public QObject
{
	Q_OBJECT
    Q_PROPERTY(QString	logLevel                READ getLogLevel                WRITE setLogLevel           )
    Q_PROPERTY(QString	logFilePath             READ getLogFilePath             WRITE setLogFilePath        )
    Q_PROPERTY(bool		logFileEnabled  		READ isLogFileEnabled   		WRITE setLogFileEnabled     )
    Q_PROPERTY(bool		logConsoleEnabled		READ isLogConsoleEnabled		WRITE setLogConsoleEnabled  )


public:
    explicit GeneralSettings();

    QString getLogLevel() {return m_logLevel;}
    QString getLogFilePath() {return m_logFilePath;}
    bool isLogFileEnabled() {return m_logFileEnabled;}
    bool isLogConsoleEnabled() {return m_logConsoleEnabled;}



signals:


public slots:
    void setLogLevel(QString val);
    void setLogFilePath(QString val);
    void setLogFileEnabled(bool val);
    void setLogConsoleEnabled(bool val);



private:
    QString m_logLevel;
    QString m_logFilePath;
    bool m_logFileEnabled;
    bool m_logConsoleEnabled;

};

#endif //__CFG_GENERAL_SETTINGS_H_
