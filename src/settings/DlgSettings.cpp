

#include "DlgSettings.h"
#include "CfgAppSettings.h"
#include "WActionManager.h"

#include "PageGeneral.h"
#include "PageScintilla.h"

#include <QIcon>

using namespace Wolverine;



DlgSettings::DlgSettings(QWidget *parent) :
    QtDialogSettings(AppSettings::instance(), parent),
    mSettings(AppSettings::instance()),
    mActionManager(ActionManager::instance())
{
    this->setWindowTitle(tr("Wolverine Settings"));
    this->setWindowIcon(QIcon(":/settings.png"));

    mInitialized = false;
}

void DlgSettings::showDialog()
{
     // All pages are deleted during deleting this dialog.
    if(!mInitialized) {
        mInitialized = true;

        Settings::PageGeneral *general = new Settings::PageGeneral(mSettings, this);
        addSettingsPage(tr("General"), general);

        Settings::PageScintilla *scintilla = new Settings::PageScintilla(mSettings, this);
        addSettingsPage(tr("Scintilla"), scintilla);

        QWidget *actionManagerWidget = mActionManager->getActionManagerWidget(this);
        addSettingsPage(tr("Key Binding"), actionManagerWidget);
    }

    // Just call exec(). QtDialogSettings is responsible for calling correct inform functions.
    if(QtDialogSettings::exec()) {
        mSettings->saveConfiguration();
        mActionManager->saveConfig();
    }

    // There is no need to keep these variables in memory.
    //delete general;
    //delete scintilla;
    //delete actionManagerWidget;
}


void DlgSettings::informToDropBackup()
{
    //Inform all external settings managers to throw backup.
    //Every internal pages works on AppSettings that does it automatically.
    mActionManager->dropConfigurationBackup();
}

void DlgSettings::informToCreateNewBackup()
{
    //Inform all external settings managers to create fresh backup (drop the previous one).
    //Every internal pages works on AppSettings that does it automatically.
    mActionManager->createConfigurationBackup();
}

void DlgSettings::informToRestoreBackup()
{
    //Inform all external settings managers to apply configuration backup.
    //Every internal pages works on AppSettings that does it automatically.
    mActionManager->restoreConfigurationBackup();
}


