#ifndef __DLG_SETTINGS_H_
  #define __DLG_SETTINGS_H_


#include "qtdialogsettings.h"

class AppSettings;



namespace Wolverine {
class ActionManager;
class EditorLexerManager;
}


namespace Wolverine {


class DlgSettings : public QtDialogSettings
{
    Q_OBJECT

public:
    explicit DlgSettings(QWidget *parent = 0);


public slots:
    void showDialog();


protected:
    virtual void informToDropBackup();
    virtual void informToCreateNewBackup();
    virtual void informToRestoreBackup();


private:
    AppSettings *mSettings;
    ActionManager *mActionManager;
    EditorLexerManager *mLexerManager;
};


}

#endif // __DLG_SETTINGS_H_
