
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


#define W_CONFIG_FILE_NAME  "appconfig"


static AppSettings* sAppConfig = 0;
static AppSettings* sStartupConfig = 0;

static void initializeAppSettings();
static inline void waitForEndOfInitialization();


/**
 *  The Initializer class
 */
class CfgInitializer : public QRunnable
{
public:
    void run()
    {
        initializeAppSettings();
    }
};



static QMutex sMutex;
static QThreadPool *sThreadPool = 0;
bool isInitializationDone = false;



/**
 *  Initializes application settings.
 *
 *  It is run in separate thread.
 */
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


/**
 *  Waits for end of initialization.
 */
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




/**
 *  Default constructor.
 *
 *  We don't want to crate specific classes here to speedup start of application.
 *  At the beggining we need only startup group.
 */
AppSettings::AppSettings()
{
    mBackup = 0;

    dynamic = 0;
    general = 0;
    hidden = 0;
    scintilla = 0;
    startup = 0;
}


/**
 *  Default destructor
 */
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


/**
 *  Initializes startup group.
 */
void AppSettings::initializeStartup()
{
    startup = new StartupSettings();

    // Load only startup settings in order to speedup application startup
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, APP_NAME, W_CONFIG_FILE_NAME);
    loadGroup(qset, startup);
}


/**
 *  Initializes full application settings object.
 *
 * @param isBackup
 */
void AppSettings::initialize(bool isBackup)
{
    if(dynamic == 0)
        dynamic = new DynamicSettings();
    if(general == 0)
        general = new GeneralSettings();
    if(hidden ==0)
        hidden = new HiddenSettings();
    if(scintilla ==0)
        scintilla = new ScintillaSettings();
    // The simplest way is to create new startup group
    // There are no benefits from copying it from sStartupConfig
    if(startup ==0)
        startup = new StartupSettings();

    if(!isBackup)
        loadConfiguration();
}


/**
 *  Creates instance of aplication settings object (startup only).
 *
 *  It should be used when application is started and we need to have only
 *  basic/startup settings. We can use only startup group in object created
 *  with this function.
 *
 * @return
 */
//static
AppSettings* AppSettings::instanceStartup()
{
    if(sStartupConfig == 0) {
        sStartupConfig = new AppSettings();
        sStartupConfig->initializeStartup();
    }
    return sStartupConfig;
}


/**
 *  Creates instance of application settings object.
 *
 * @return
 */
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


/**
 *  Creates instance of application settings object in separate thread.
 *
 *  It should be called as soon as possible. Settings are loaded to speedup starting
 *  of application.
 */
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


/**
 *  Removes instance of application settings.
 *
 *  Normally it is called automatically when application is closed. It can be called
 *  manually e.g. when application is called to print help - QApplication object is not
 *  created.
 */
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



/**
 *  Loads configuration from a file.
 *
 * @return
 */
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


/**
 *  Saves configuration to a file.
 *
 * @return
 */
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

/**
 * Copies application settings instance.
 *
 * @param to
 * @param from
 */
void AppSettings::copy(AppSettings *to, const AppSettings *from)
{
    copyGroup(to->dynamic,   from->dynamic);
    copyGroup(to->general,   from->general);
    copyGroup(to->hidden,    from->hidden);
    copyGroup(to->scintilla, from->scintilla);
    copyGroup(to->startup,   from->startup);
}


/**
 *  Creates backup.
 */
//virtual
void AppSettings::createConfigurationBackup()
{
    if(mBackup)
        delete mBackup;
    mBackup = new AppSettings();
    mBackup->initialize(true);
    copy(mBackup, sAppConfig);
}


/**
 *  Restores backup.
 */
//virtual
void AppSettings::restoreConfigurationBackup()
{
    if(mBackup) {
        copy(sAppConfig, mBackup);
        delete mBackup;
        mBackup = 0;
    }
}


/**
 *  Throws backup away.
 */
//virtual
void AppSettings::dropConfigurationBackup()
{
    if(mBackup) {
        delete mBackup;
        mBackup = 0;
    }
}


