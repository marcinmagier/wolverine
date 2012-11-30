/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       CfgAppSettings.h
 *  @brief      AppSettings class interface.
 */

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

    void initialize(bool isBackup = false);
    virtual bool loadConfiguration();
    virtual bool saveConfiguration();

    virtual void createConfigurationBackup();
    virtual void restoreConfigurationBackup();
    virtual void dropConfigurationBackup();


private:
    AppSettings();

    void initializeStartup();
    void copy(AppSettings *to, const AppSettings *from);

    AppSettings *mBackup;
};

#endif //__CFG_APP_SETTINGS_H_
