
#include "wolverine_cfg.h"
#include "CfgAppSettings.h"
#include "CfgStartupSettings.h"
#include "WMainWindow.h"

#include "Logger.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"

#include "qtsingleapplication.h"

#include <QApplication>
#include <QTextStream>
#include <QStringList>
#include <QFileInfo>



static void configureLogger();

static void printHelp();
static void printVersion();
static int runNevInstanceApp(int argc, char **argv, const QStringList &files);
static int runSingleInstanceApp(int argc, char **argv, const QStringList &files);



/**
 *  Configures logger.
 */
void configureLogger()
{
    AppSettings *settings = AppSettings::instanceStartup();

    if(settings->startup->isLogConsoleEnabled()) {
        ConsoleAppender *console = new ConsoleAppender();   //qtlogger library is responsible for deleting console appender
        console->setFormat(LOG_FORMAT_STRING);
        console->setDetailsLevel(settings->startup->getLogLevel());
        Logger::registerAppender(console);
    }

    if(settings->startup->isLogFileEnabled()) {
        QString logFile = settings->startup->getLogFilePath();
        if(logFile.isEmpty()) {
            LOG_ERROR("No log file selected");
            return;
        }
        FileAppender *file = new FileAppender(logFile); //qtlogger library is responsible for deleting file appender
        file->setFormat(LOG_FORMAT_STRING);
        file->setDetailsLevel(settings->startup->getLogLevel());
        Logger::registerAppender(file);
    }
}


/**
 *  Prints help text.
 */
void printHelp()
{
    QTextStream out(stdout);
    out << "Usage:\n"
        << "  Wolverine <file>[:<line>] ...\n"
        << "  Wolverine --new <file>\n"
        << "  Wolverine --help\n"
        << "  Wolverine --version\n";
}


/**
 *  Prints app version.
 */
void printVersion()
{
    QTextStream out(stdout);
    out << APP_NAME << " ver " << APP_VERSION << "\n";
}


/**
 *  Runs new instance of application.
 *
 * @param argc
 * @param argv
 * @param files
 * @return
 */
int runNevInstanceApp(int argc, char **argv, const QStringList &files)
{
    QApplication app(argc, argv);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);

    AppSettings::instanceWithNewThread();

    Wolverine::MainWindow mainWindow;

    foreach(QString file, files) {
        mainWindow.openFile(file);
    }

    mainWindow.show();

    return app.exec();
}


/**
 *  Runs single instance of application.
 *
 * @param argc
 * @param argv
 * @param files
 * @return
 */
int runSingleInstanceApp(int argc, char **argv, const QStringList &files)
{
    QtSingleApplication app(argc, argv);

    if(app.isRunning()) {
        foreach(QString file, files) {
            app.sendMessage(file);
        }
        AppSettings::deleteInstance();
        return 0;
    }

    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERSION);
    AppSettings::instanceWithNewThread();

    Wolverine::MainWindow mainWindow;

    QObject::connect(&app, SIGNAL(messageReceived(const QString&)),
                     &mainWindow, SLOT(openFile(const QString&)));

    mainWindow.show();

    return app.exec();
}




int main(int argc, char **argv)
{
    bool isNewInstance = false;
    QStringList files;
    AppSettings *settings = AppSettings::instanceStartup();

    configureLogger();

    // Process arguments, create files list to be opened
    // Ommit program path (1st arg)
    for(int i=1; i<argc; ++i) {
        QString str(argv[i]);

        if(str.compare("-h")==0 || str.compare("--help")==0) {
            printHelp();
            AppSettings::deleteInstance();
            return 0;
        }
        if(str.compare("-v")==0 || str.compare("--version")==0) {
            printVersion();
            AppSettings::deleteInstance();
            return 0;
        }
        if(str.compare("-n")==0 || str.compare("--new")==0) {
            isNewInstance = false;
        }

        if(!QFileInfo(str).exists()) {
            continue;
        }

        files << QFileInfo(str).absoluteFilePath();
    }

    if(isNewInstance || settings->startup->isAlwaysNewInstance())
        return runNevInstanceApp(argc, argv, files);

    return runSingleInstanceApp(argc, argv, files);
}


