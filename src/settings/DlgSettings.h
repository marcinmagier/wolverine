#ifndef __DLG_SETTINGS_H_
  #define __DLG_SETTINGS_H_


#include "qtdialogsettings.h"
#include "CfgAppSettings.h"


namespace Wolverine {


class DlgSettings : public QtDialogSettings
{
    Q_OBJECT

public:
    explicit DlgSettings(CfgAppSettings *settings, QWidget *parent = 0);
    

public slots:
    void showDialog();

private:
    CfgAppSettings *m_settings;
    
};


}

#endif // __DLG_SETTINGS_H_
