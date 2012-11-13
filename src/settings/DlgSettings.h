#ifndef __DLG_SETTINGS_H_
  #define __DLG_SETTINGS_H_


#include "qtdialogsettings.h"

class AppSettings;



namespace Wolverine {


class DlgSettings : public QtDialogSettings
{
    Q_OBJECT

public:
    explicit DlgSettings(AppSettings *settings, QWidget *parent = 0);
    

public slots:
    void showDialog();

private:
    AppSettings *mSettings;
    bool mInitialized;
};


}

#endif // __DLG_SETTINGS_H_
