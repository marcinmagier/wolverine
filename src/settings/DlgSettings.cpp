

#include "DlgSettings.h"
#include "PageGeneral.h"

#include <QIcon>

using namespace Wolverine;


DlgSettings::DlgSettings(CfgAppSettings *settings, QWidget *parent) :
    QtDialogSettings(settings, parent), m_settings(settings)
{
    this->setWindowTitle(tr("Wolverine Settings"));
    this->setWindowIcon(QIcon(":/settings.png"));

}

void DlgSettings::showDialog()
{
    Settings::PageGeneral *general = new Settings::PageGeneral(m_settings, this);
    addSettingsPage("General", general);
    exec();
}
