
#ifndef __APP_SETTINGS_H_
 #define __APP_SETTINGS_H_

#include "qtconfig.h"

#include "GeneralSettings.h"
#include "HiddenSettings.h"
#include "ScintillaSettings.h"


class AppConfig : public QtConfig
{
private:
    AppConfig() {};
	
public:
    GeneralSettings general;
    HiddenSettings hidden;
    ScintillaSettings scintilla;

    static AppConfig* getInstance();
    virtual bool loadConfiguration();
    virtual bool saveConfiguration();

private:
    static AppConfig *s_settings;
};

#endif //__APP_SETTINGS_H_
