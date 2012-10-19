
#ifndef __CFG_APP_SETTINGS_H_
 #define __CFG_APP_SETTINGS_H_

#include "qtconfig.h"

#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
#include "CfgScintillaSettings.h"


class CfgAppSettings : public QtConfig
{
private:
    CfgAppSettings() {};
	
public:
    CfgGeneralSettings general;
    CfgHiddenSettings hidden;
    CfgScintillaSettings scintilla;

    static CfgAppSettings* instance();
    virtual bool loadConfiguration();
    virtual bool saveConfiguration();

private:
    static CfgAppSettings *s_appconfig;
};

#endif //__CFG_APP_SETTINGS_H_
