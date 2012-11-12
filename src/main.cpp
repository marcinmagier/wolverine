
#include "wolverine_cfg.h"
#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"
#include "WMainWindow.h"

#include "Logger.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"

#include <QApplication>



static void configureLogger();




void configureLogger()
{
    AppSettings *settings = AppSettings::instance();

    if(settings->general->isLogConsoleEnabled()) {
        ConsoleAppender *console = new ConsoleAppender();   //qtlogger library is responsible for deleting console appender
        console->setFormat(LOG_FORMAT_STRING);
        console->setDetailsLevel(settings->general->getLogLevel());
        Logger::registerAppender(console);
    }

    if(settings->general->isLogFileEnabled()) {
        QString logFile = settings->general->getLogFilePath();
        if(logFile.isEmpty()) {
            LOG_ERROR("No log file selected");
            return;
        }
        FileAppender *file = new FileAppender(logFile); //qtlogger library is responsible for deleting file appender
        file->setFormat(LOG_FORMAT_STRING);
        file->setDetailsLevel(settings->general->getLogLevel());
        Logger::registerAppender(file);
    }
}




int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);

    configureLogger();


    Wolverine::MainWindow mainWindow;

    mainWindow.show();


    return app.exec();
}
