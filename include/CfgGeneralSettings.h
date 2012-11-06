
#ifndef __CFG_GENERAL_SETTINGS_H_
 #define __CFG_GENERAL_SETTINGS_H_

#include <QObject>
#include <QString>

class GeneralSettings : public QObject
{
	Q_OBJECT
    Q_PROPERTY(QString	logLevel                READ getLogLevel                WRITE setLogLevel)
    Q_PROPERTY(bool		logConsoleEnabled		READ isLogConsoleEnabled		WRITE setLogConsoleEnabled)
    Q_PROPERTY(bool		logFileEnabled  		READ isLogFileEnabled   		WRITE setLogFileEnabled)

public:
    explicit GeneralSettings();

    QString getLogLevel() {return m_logLevel;}
    bool isLogConsoleEnabled() {return m_logConsoleEnabled;}
    bool isLogFileEnabled() {return m_logFileEnabled;}


signals:
    void logLevelChanged(QString val);
    void logConsoleEnabledChanged(bool val);
    void logFileEnabledChanged(bool val);


public slots:
    void setLogLevel(QString val);
    void setLogConsoleEnabled(bool val);
    void setLogFileEnabled(bool val);


private:
    QString m_logLevel;
    bool m_logConsoleEnabled;
    bool m_logFileEnabled;
};

#endif //__CFG_GENERAL_SETTINGS_H_
