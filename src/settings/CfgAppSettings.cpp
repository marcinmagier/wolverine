/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       CfgAppSettings.cpp
 *  @brief      AppSettings class implementation.
 */


#include "wolverine_cfg.h"

#include "CfgAppSettings.h"
#include "CfgDynamicSettings.h"
#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
#include "CfgScintillaSettings.h"
#include "CfgStartupSettings.h"
#include "CfgViewSettings.h"

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


static AppSettings* sAppSettingsInstance = 0;
static AppSettings* sStartupSettingsInstance = 0;

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
//static
void initializeAppSettings()
{
    sAppSettingsInstance->initialize();
    qAddPostRoutine(AppSettings::deleteInstance);

    if(sStartupSettingsInstance) {
        delete sStartupSettingsInstance;
        sStartupSettingsInstance = 0;
    }

    isInitializationDone = true;
}


/**
 *  Waits for end of initialization.
 */
//static
void waitForEndOfInitialization()
{
    if(!isInitializationDone) {
        sMutex.lock();
        if(!isInitializationDone && sThreadPool) {
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
    view = 0;
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
    if(view)
        delete view;
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
    if(hidden == 0)
        hidden = new HiddenSettings();
    if(scintilla == 0)
        scintilla = new ScintillaSettings();
    // The simplest way is to create new startup group
    // There are no benefits from copying it from sStartupSettingsInstance, code would be quite difficult
    if(startup ==0)
        startup = new StartupSettings();
    if(view == 0)
        view = new ViewSettings();

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
    if(sStartupSettingsInstance == 0) {
        sStartupSettingsInstance = new AppSettings();
        sStartupSettingsInstance->initializeStartup();
    }
    return sStartupSettingsInstance;
}


/**
 *  Creates instance of application settings object.
 *
 * @return
 */
//static
AppSettings* AppSettings::instance()
{
    if(sAppSettingsInstance == 0) {
        sMutex.lock();
        if(sAppSettingsInstance == 0) {
            // Initialization not started yet, do it now
            sAppSettingsInstance = new AppSettings();
            initializeAppSettings();
            sMutex.unlock();
            return sAppSettingsInstance;
        }
        sMutex.unlock();
    }

    waitForEndOfInitialization();

    return sAppSettingsInstance;
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
    if(sAppSettingsInstance == 0) {
        sMutex.lock();
        if(sAppSettingsInstance == 0) {
            sAppSettingsInstance = new AppSettings();
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

    if(sAppSettingsInstance) {
        sAppSettingsInstance->dropConfigurationBackup();
        sAppSettingsInstance->saveConfiguration();
        delete sAppSettingsInstance;
        sAppSettingsInstance = 0;
    }

    if(sStartupSettingsInstance) {
        delete sStartupSettingsInstance;
        sStartupSettingsInstance = 0;
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
    loadGroup(qset, view);
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
    saveGroup(qset, view);
	return true;
}

/**
 *  Copies application settings instance.
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
    copyGroup(to->view,      from->view);
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
    copy(mBackup, sAppSettingsInstance);
}


/**
 *  Restores backup.
 */
//virtual
void AppSettings::restoreConfigurationBackup()
{
    if(mBackup) {
        copy(sAppSettingsInstance, mBackup);
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
