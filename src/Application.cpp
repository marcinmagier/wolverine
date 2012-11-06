
#include "WApplication.h"
#include "CfgAppSettings.h"
#include "Logger.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"

#include <QApplication>


#define APP_NAME            "Wolverine"
#define LOG_FORMAT_STRING   "%t{yyyy-MM-dd mm:ss} [%-7L] %F %i <%C> %m\n"
#define LOG_FILE_NAME       "Wolverine.log"


using namespace Wolverine;


Application* Application::s_application = 0;


Application::Application() :
    m_logConsoleAppender(0), m_logFileAppender(0)
{
    qApp->setApplicationName(APP_NAME);
    m_settings = CfgAppSettings::instance();

    if(m_settings->general.isLogConsoleEnabled()) {
        enableLogConsole(true);
    }

    if(m_settings->general.isLogFileEnabled()) {
        enableLogFile(true);
    }
}


Application::~Application()
{
    m_settings->saveConfiguration();
    delete m_settings;

}


Application* Application::instance()
{
    if(s_application == 0) {
        s_application = new Application();
    }

    return s_application;
}


void Application::setLogDetailsLevel(const QString &level)
{
    if(m_logConsoleAppender)
        m_logConsoleAppender->setDetailsLevel(level);

    if(m_logFileAppender)
        m_logFileAppender->setDetailsLevel(level);
}

void Application::enableLogConsole(bool enabled)
{
    if(m_logConsoleAppender != 0) {
        delete m_logConsoleAppender;
        m_logConsoleAppender = 0;
    }

    if(enabled) {
        m_logConsoleAppender = new ConsoleAppender();
        m_logConsoleAppender->setFormat(LOG_FORMAT_STRING);
        m_logConsoleAppender->setDetailsLevel(m_settings->general.getLogLevel());
        Logger::registerAppender(m_logConsoleAppender);

    }
}

void Application::enableLogFile(bool enabled)
{
    if(m_logFileAppender != 0) {
        delete m_logFileAppender;
        m_logFileAppender = 0;
    }

    if(enabled) {
        m_logFileAppender = new FileAppender(LOG_FILE_NAME);
        m_logFileAppender->setFormat(LOG_FORMAT_STRING);
        m_logFileAppender->setDetailsLevel(m_settings->general.getLogLevel());
        Logger::registerAppender(m_logFileAppender);
    }
}
