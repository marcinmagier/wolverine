

#include "DlgSettings.h"
#include "CfgAppSettings.h"
#include "qtactionmanager.h"

#include "PageGeneral.h"
#include "PageScintilla.h"

#include <QIcon>

using namespace Wolverine;



DlgSettings::DlgSettings(CfgAppSettings *settings, QWidget *parent) :
    QtDialogSettings(settings, parent), m_settings(settings)
{
    this->setWindowTitle(tr("Wolverine Settings"));
    this->setWindowIcon(QIcon(":/settings.png"));

    m_actionManager = QtActionManager::instance();
}

void DlgSettings::showDialog()
{
    Settings::PageGeneral *general = new Settings::PageGeneral(m_settings, this);
    addSettingsPage(tr("General"), general);

    Settings::PageScintilla *scintilla = new Settings::PageScintilla(m_settings, this);
    addSettingsPage(tr("Scintilla"), scintilla);

    QWidget *actionManagerWidget = m_actionManager->getActionManagerWidget(this);
    addSettingsPage(tr("Key Binding"), actionManagerWidget);

    exec();

    delete general;
    delete scintilla;
    delete actionManagerWidget;
}
