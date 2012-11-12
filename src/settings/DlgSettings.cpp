

#include "DlgSettings.h"
#include "CfgAppSettings.h"
#include "qtactionmanager.h"

#include "PageGeneral.h"
#include "PageScintilla.h"

#include <QIcon>

using namespace Wolverine;



DlgSettings::DlgSettings(AppSettings *settings, QWidget *parent) :
    QtDialogSettings(settings, parent), mSettings(settings)
{
    this->setWindowTitle(tr("Wolverine Settings"));
    this->setWindowIcon(QIcon(":/settings.png"));

    mInitialized = false;
}

void DlgSettings::showDialog()
{
     // All pages are deleted when this dialog is.
    if(!mInitialized) {
        mInitialized = true;

        Settings::PageGeneral *general = new Settings::PageGeneral(mSettings, this);
        addSettingsPage(tr("General"), general);

        Settings::PageScintilla *scintilla = new Settings::PageScintilla(mSettings, this);
        addSettingsPage(tr("Scintilla"), scintilla);

        QWidget *actionManagerWidget = QtActionManager::instance()->getActionManagerWidget(this);
        addSettingsPage(tr("Key Binding"), actionManagerWidget);
    }

    exec();
}
