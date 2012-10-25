#ifndef __DLG_SETTINGS_H_
  #define __DLG_SETTINGS_H_


#include "qtdialogsettings.h"

class CfgAppSettings;
class QtActionManager;


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
    QtActionManager *m_actionManager;
};


}

#endif // __DLG_SETTINGS_H_
