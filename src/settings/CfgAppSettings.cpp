
#include "wolverine_cfg.h"

#include "CfgAppSettings.h"
#include "CfgDynamicSettings.h"
#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
#include "CfgScintillaSettings.h"
#include "CfgStartupSettings.h"

#include <QApplication>
#include <QMetaObject>
#include <QMetaProperty>
#include <QVariant>
#include <QSettings>

#include <QMutex>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>

#include <QDebug>


#define W_CONFIG_FILE_NAME  "appconfig"


static AppSettings* sAppConfig = 0;
static AppSettings* sStartupConfig = 0;

void initializeAppSettings();
static inline void waitForEndOfInitialization();


/**
 *  The Initializer class
 */
class CfgInitializer : public QRunnable
{
public:
    ~CfgInitializer();

    void run()
    {
        initializeAppSettings();
    }
};

CfgInitializer::~CfgInitializer()
{
    qDebug() << "Destructor";
}

static QMutex sMutex;
static QThreadPool *sThreadPool = 0;
bool isInitializationDone = false;




void initializeAppSettings()
{
    sAppConfig->initialize();
    qAddPostRoutine(AppSettings::deleteInstance);

    if(sStartupConfig) {
        delete sStartupConfig;
        sStartupConfig = 0;
    }

    isInitializationDone = true;
}


void waitForEndOfInitialization()
{
    if(!isInitializationDone) {
        sMutex.lock();
        if(!isInitializationDone) {
            // Initialization pending, we have to wait
            sThreadPool->waitForDone();
        }
        sMutex.unlock();
    }
}




AppSettings::AppSettings()
{
    mBackup = 0;

    dynamic = 0;
    general = 0;
    hidden = 0;
    scintilla = 0;
    startup = 0;
}

AppSettings::~AppSettings()
{
    if(dynamic)
        delete dynamic;
    if(general)
        delete general;
    if(hidden)
        delete hidden;
    if(scintilla)
        delete scintilla;
    if(startup)
        delete startup;
}

void AppSettings::initialize(bool isBackup)
{
    dynamic = new DynamicSettings();
    general = new GeneralSettings();
    hidden = new HiddenSettings();
    scintilla = new ScintillaSettings();
    // The simplest way is to create new startup group
    startup = new StartupSettings();

    if(!isBackup)
        loadConfiguration();
}

void AppSettings::initializeStartup()
{
    startup = new StartupSettings();

    // Load only startup settings in order to speedup application startup
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, APP_NAME, W_CONFIG_FILE_NAME);
    loadGroup(qset, startup);
}


//static
AppSettings* AppSettings::instanceStartup()
{
    if(sStartupConfig == 0) {
        sStartupConfig = new AppSettings();
        sStartupConfig->initializeStartup();
    }
    return sStartupConfig;
}


//static
AppSettings* AppSettings::instance()
{
    if(sAppConfig == 0) {
        sMutex.lock();
        if(sAppConfig == 0) {
            // Initialization not started yet, do it now
            sAppConfig = new AppSettings();
            initializeAppSettings();
            sMutex.unlock();
            return sAppConfig;
        }
        sMutex.unlock();
    }

    waitForEndOfInitialization();

    return sAppConfig;
}


//static
void AppSettings::instanceWithNewThread()
{
    if(sAppConfig == 0) {
        sMutex.lock();
        if(sAppConfig == 0) {
            sAppConfig = new AppSettings();
            sThreadPool = QThreadPool::globalInstance();
            // Initializer is deleted automaticaly after finishing its job.
            sThreadPool->start(new CfgInitializer());
        }
        sMutex.unlock();
    }
}

//static
void AppSettings::deleteInstance()
{
    // Just to sleep well
    waitForEndOfInitialization();

    if(sAppConfig) {
        sAppConfig->dropConfigurationBackup();
        sAppConfig->saveConfiguration();
        delete sAppConfig;
        sAppConfig = 0;
    }

    if(sStartupConfig) {
        delete sStartupConfig;
        sStartupConfig = 0;
    }

}


//virtual
bool AppSettings::loadConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, APP_NAME, W_CONFIG_FILE_NAME);

    loadGroup(qset, general);
    loadGroup(qset, hidden);
    loadGroup(qset, scintilla);
    loadGroup(qset, startup);       //In worst case startup settings are loaded twice.
	return true;
}

//virtual
bool AppSettings::saveConfiguration()
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, APP_NAME, W_CONFIG_FILE_NAME);

    if (!qset.isWritable())
        return false;

    saveGroup(qset, general);
    saveGroup(qset, hidden);
    saveGroup(qset, scintilla);
    saveGroup(qset, startup);
	return true;
}

void AppSettings::copy(AppSettings *to, const AppSettings *from)
{
    copyGroup(to->dynamic,   from->dynamic);
    copyGroup(to->general,   from->general);
    copyGroup(to->hidden,    from->hidden);
    copyGroup(to->scintilla, from->scintilla);
    copyGroup(to->startup,   from->startup);
}


//virtual
void AppSettings::createConfigurationBackup()
{
    if(mBackup)
        delete mBackup;
    mBackup = new AppSettings();
    mBackup->initialize(true);
    copy(mBackup, sAppConfig);
}


//virtual
void AppSettings::restoreConfigurationBackup()
{
    if(mBackup) {
        copy(sAppConfig, mBackup);
        delete mBackup;
        mBackup = 0;
    }
}


//virtual
void AppSettings::dropConfigurationBackup()
{
    if(mBackup) {
        delete mBackup;
        mBackup = 0;
    }
}


