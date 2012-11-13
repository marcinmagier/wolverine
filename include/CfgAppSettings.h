
#ifndef __CFG_APP_SETTINGS_H_
 #define __CFG_APP_SETTINGS_H_

#include "qtconfig.h"

class QString;
class DynamicSettings;
class GeneralSettings;
class HiddenSettings;
class ScintillaSettings;



class AppSettings : public QtConfig
{

public:
    DynamicSettings *dynamic;
    GeneralSettings *general;
    HiddenSettings *hidden;
    ScintillaSettings *scintilla;


    virtual ~AppSettings();
    static AppSettings* instance();
    virtual bool loadConfiguration();
    virtual bool saveConfiguration();

    virtual void createConfigurationBackup();
    virtual void restoreConfigurationBackup();
    virtual void dropConfigurationBackup();


private:
    AppSettings();

    void copy(AppSettings *to, const AppSettings *from);

    static const QString sConfigFileName;
    AppSettings *mBackup;

};

#endif //__CFG_APP_SETTINGS_H_
