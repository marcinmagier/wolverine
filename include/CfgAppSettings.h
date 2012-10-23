
#ifndef __CFG_APP_SETTINGS_H_
 #define __CFG_APP_SETTINGS_H_

#include "qtconfig.h"

#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
#include "CfgScintillaSettings.h"


class CfgAppSettings : public QtConfig
{

public:
    CfgGeneralSettings general;
    CfgHiddenSettings hidden;
    CfgScintillaSettings scintilla;


    static CfgAppSettings* instance();
    virtual bool loadConfiguration();
    virtual bool saveConfiguration();

    virtual void createConfigurationBackup();
    virtual void restoreConfigurationBackup();
    virtual void dropConfigurationBackup();


private:
    CfgAppSettings() {}

    void copy(CfgAppSettings *to, const CfgAppSettings *from);

    static CfgAppSettings *s_appconfig;
    static CfgAppSettings *s_backup;
};

#endif //__CFG_APP_SETTINGS_H_
