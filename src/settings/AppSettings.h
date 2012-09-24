
#include "Settings.h"

#include "GeneralSettings.h"
#include "HiddenSettings.h"
#include "ScintillaSettings.h"


class AppSettings : public Settings
{
	
public:
    GeneralSettings general;
    HiddenSettings hidden;
    ScintillaSettings scintilla;

	virtual bool readSettings();
	virtual bool writeSettings();
};