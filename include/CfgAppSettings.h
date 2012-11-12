
#ifndef __CFG_APP_SETTINGS_H_
 #define __CFG_APP_SETTINGS_H_

#include "qtconfig.h"

#include "CfgGeneralSettings.h"
#include "CfgHiddenSettings.h"
#include "CfgScintillaSettings.h"
#include "CfgTempSettings.h"


class AppSettings : public QtConfig
{

public:
    GeneralSettings *general;
    HiddenSettings *hidden;
    ScintillaSettings *scintilla;
    TempSettings *temp;


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

    static const QString sConfigFile;
    AppSettings *m_backup;

    friend class TempSettings;
};

#endif //__CFG_APP_SETTINGS_H_
