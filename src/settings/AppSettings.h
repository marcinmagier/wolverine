
#include "Settings.h"

#include "GeneralSettings.h"
#include "HiddenSettings.h"
#include "ScintillaSettings.h"


class AppSettings : public Settings
{
private:
    AppSettings() {};
	
public:
    GeneralSettings general;
    HiddenSettings hidden;
    ScintillaSettings scintilla;

    static AppSettings* getInstance();
	virtual bool readSettings();
	virtual bool writeSettings();

private:
    static AppSettings *s_settings;
};
