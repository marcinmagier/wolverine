
#include "WMainWindow.h"

#include "qtactionmanager.h"
#include "CfgAppSettings.h"
#include "DlgSettings.h"



using namespace Wolverine;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_settings = CfgAppSettings::instance();
    m_actionManager = QtActionManager::instance();
    m_settingsDialog = new DlgSettings(m_settings, this);

    this->resize(m_settings->hidden.getSize());
    this->move(m_settings->hidden.getPosition());
}

MainWindow::~MainWindow()
{
    m_settings->hidden.setPosition(this->pos());
    m_settings->hidden.setSize(this->size());

    delete m_settingsDialog;
    delete m_actionManager;
    delete m_settings;

}

void MainWindow::createMenusAndToolbars()
{

}
