
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


Application::Application()
{
    qApp->setApplicationName(APP_NAME);
    m_settings = CfgAppSettings::instance();

    m_logConsoleAppender = new ConsoleAppender();
    m_logConsoleAppender->setFormat(LOG_FORMAT_STRING);
    Logger::registerAppender(m_logConsoleAppender);

    m_logFileAppender = new FileAppender(LOG_FILE_NAME);
    m_logFileAppender->setFormat(LOG_FORMAT_STRING);
    Logger::registerAppender(m_logFileAppender);

    setLogDetailsLevel("Error");
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
    m_logConsoleAppender->setDetailsLevel(level);
    m_logFileAppender->setDetailsLevel(level);
}

