#ifndef __DLG_SETTINGS_H_
  #define __DLG_SETTINGS_H_


#include "qtdialogsettings.h"

class AppSettings;
class QtActionManager;


namespace Wolverine {


class DlgSettings : public QtDialogSettings
{
    Q_OBJECT

public:
    explicit DlgSettings(AppSettings *settings, QWidget *parent = 0);
    

public slots:
    void showDialog();

private:
    AppSettings *m_settings;
    QtActionManager *m_actionManager;
};


}

#endif // __DLG_SETTINGS_H_
