
#ifndef __CFG_APP_SETTINGS_H_
 #define __CFG_APP_SETTINGS_H_

#include "qtconfig.h"

class QString;
class DynamicSettings;
class GeneralSettings;
class HiddenSettings;
class ScintillaSettings;
class StartupSettings;



class AppSettings : public QtConfig
{

public:
    DynamicSettings *dynamic;
    GeneralSettings *general;
    HiddenSettings *hidden;
    ScintillaSettings *scintilla;
    StartupSettings *startup;


    virtual ~AppSettings();

    static AppSettings* instance();
    static AppSettings* instanceStartup();
    static void instanceWithNewThread();
    static void deleteInstance();

    virtual bool loadConfiguration();
    virtual bool saveConfiguration();

    virtual void createConfigurationBackup();
    virtual void restoreConfigurationBackup();
    virtual void dropConfigurationBackup();


private:
    AppSettings();

    void initialize(bool isBackup = false);
    void initializeStartup();

    void copy(AppSettings *to, const AppSettings *from);



    static AppSettings* sAppConfig;
    static AppSettings* sStartupConfig;

    AppSettings *mBackup;
};

#endif //__CFG_APP_SETTINGS_H_
