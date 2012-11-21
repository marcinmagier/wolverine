

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

    exec();
}
