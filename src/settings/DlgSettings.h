#ifndef __DLG_SETTINGS_H_
  #define __DLG_SETTINGS_H_


#include "qtdialogsettings.h"

class AppSettings;



namespace Wolverine {
class ActionManager;
}


namespace Wolverine {


class DlgSettings : public QtDialogSettings
{
    Q_OBJECT

public:
    explicit DlgSettings(QWidget *parent = 0);
    

public slots:
    void showDialog();

private:
    AppSettings *mSettings;
    ActionManager *mActionManager;
    bool mInitialized;
};


}

#endif // __DLG_SETTINGS_H_
