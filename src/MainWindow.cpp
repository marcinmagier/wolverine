
#include "WMainWindow.h"

#include "qtactionmanager.h"
#include "CfgAppSettings.h"
#include "DlgSettings.h"



using namespace Wolverine;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_settings = AppSettings::instance();
    m_actionManager = QtActionManager::instance();
    m_settingsDialog = new DlgSettings(m_settings, this);

    this->resize(m_settings->hidden->getMWSize());
    this->move(m_settings->hidden->getMWPosition());
}

MainWindow::~MainWindow()
{
    m_settings->hidden->setMWPosition(this->pos());
    m_settings->hidden->setMWSize(this->size());

    delete m_settingsDialog;
}

void MainWindow::createMenusAndToolbars()
{

}
