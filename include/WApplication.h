#ifndef __W_APPLICATION_H_
 #define __W_APPLICATION_H_


#include <QObject>

class QString;
class ConsoleAppender;
class FileAppender;
class CfgAppSettings;



namespace Wolverine
{


class Application : public QObject
{
    Q_OBJECT

private:
    explicit Application();

public:
    virtual ~Application();
    static Application* instance();

public slots:
    void setLogDetailsLevel(const QString &level);


private:
    static Application *s_application;
    ConsoleAppender *m_logConsoleAppender;
    FileAppender *m_logFileAppender;
    CfgAppSettings *m_settings;

};


}


#endif // __W_APPLICATION_H_
