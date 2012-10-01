
#ifndef __APP_CONFIG_H_
 #define __APP_CONFIG_H_

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

    static AppConfig* instance();
    virtual bool loadConfiguration();
    virtual bool saveConfiguration();

private:
    static AppConfig *s_appconfig;
};

#endif //__APP_CONFIG_H_
