/**************************************************************************************************
**
**  Copyright (C) 2012-2013 Magier Marcin
**
**  This program is free software: you can redistribute it and/or modify it under the terms 
**  of the GNU General Public License as published by the Free Software Foundation, 
**  either version 3 of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
**  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
**  See the GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************************************/

/**
 *  @file       main.cpp
 *  @brief      Main function.
 */



#include "wolverine_cfg.h"
#include "CfgAppSettings.h"
#include "CfgDynamicSettings.h"
#include "CfgStartupSettings.h"
#include "WLib.h"
#include "WMainWindow.h"
#include "WActionManager.h"

#include "Logger.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"

#include "qtsingleapplication.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QTextStream>
#include <QStringList>
#include <QFileInfo>
#include <QDir>



static void configureLogger();
static void loadTranslations(QApplication *app);
static void appInit(QApplication *app);

static void printHelp();
static void printVersion();
static int runNevInstanceApp(int argc, char **argv);
static int runSingleInstanceApp(int argc, char **argv);



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
 *  Loads translator according to current language.
 *
 * @param app
 */
void loadTranslations(QApplication *app)
{
    AppSettings *settings = AppSettings::instanceStartup();

    QString lang = settings->startup->getLanguage();
    if(lang.isEmpty())
        lang = QLocale::system().name();

    // We don't want to wait for dynamic settings so calculate translation path ad hoc
    QString tmpDir = app->applicationDirPath();
    tmpDir = QDir(tmpDir).absoluteFilePath("translations");
    QTranslator *translator = new QTranslator();
    if(translator->load("wolverine_"+lang, tmpDir)) {
        if(!translator->isEmpty())
            app->installTranslator(translator);
    }
    delete translator;
}


/**
 *  Initializes new application.
 *
 * @param app
 */
void appInit(QApplication *app)
{
    app->setApplicationName(APP_NAME);
    app->setApplicationVersion(APP_VERSION);

    // Initialize full settings class (with new thread) just after application name is set.
    AppSettings::instanceWithNewThread();

    loadTranslations(app);
    // We can initialize actions after translations are loaded
    Wolverine::ActionManager::instanceWithNewThread();

    // Make icons visible in menus (on Linux menus icons are switched off by default)
    app->setAttribute(Qt::AA_DontShowIconsInMenus, false);
}


/**
 *  Prints help text.
 */
void printHelp()
{
    QTextStream out(stdout);
    out << "Usage:\n"
        << "  Wolverine <file1>[@<line1>] <file2>[@<line2>] ... [<line>]\n"
        << "  Wolverine --new <file1>[@<line1>] <file2>[@<line2>] ... [<line>]\n"
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
int runNevInstanceApp(int argc, char **argv)
{
    QApplication app(argc, argv);

    LOG_DEBUG("New app instance is starting with --new.");
    appInit(&app);

    Wolverine::MainWindow mainWindow;

    QStringList files = Wolverine::Lib::createFileListFromArgs(argc, argv);
    if(files.count() > 0) {
        foreach(QString file, files) {
            mainWindow.openFile(file);
        }
    } else {
        mainWindow.openNewFile();
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
int runSingleInstanceApp(int argc, char **argv)
{
    QtSingleApplication app(argc, argv);
    QStringList files = Wolverine::Lib::createFileListFromArgs(argc, argv);

    if(app.sendMessage("")) {
        LOG_INFO("Application is already started");
        foreach(QString file, files) {
            app.sendMessage(file);
         }
        AppSettings::deleteInstance();
        return 0;
    }

    LOG_DEBUG("New app instance is starting.");
    appInit(&app);

    Wolverine::MainWindow mainWindow;
    if(files.count() > 0) {
        foreach(QString file, files) {
            mainWindow.openFile(file);
        }
    } else {
        mainWindow.openNewFile();
    }
    QObject::connect(&app, SIGNAL(messageReceived(const QString&)),
                     &mainWindow, SLOT(openFile(const QString&)));

    mainWindow.show();
    return app.exec();
}




int main(int argc, char **argv)
{
    bool isNewInstance = false;
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
            isNewInstance = true;
            continue;
        }
    }

    Wolverine::Lib::setAppFile(QString(argv[0]));

    if(isNewInstance || settings->startup->isAlwaysNewInstance())
        return runNevInstanceApp(argc, argv);

    return runSingleInstanceApp(argc, argv);
}


