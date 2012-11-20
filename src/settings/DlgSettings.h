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
    explicit DlgSettings(ActionManager *actionManager, QWidget *parent = 0);
    

public slots:
    void showDialog();

private:
    ActionManager *mActionManager;
    AppSettings *mSettings;
    bool mInitialized;
};


}

#endif // __DLG_SETTINGS_H_
