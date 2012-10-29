
#include "CfgAppSettings.h"
#include "qtmanagedtoolbar.h"
#include "qtactionmanager.h"
#include "DlgSettings.h"


#include "Logger.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"

#include <QApplication>
#include <QMainWindow>
#include <QtGui>


class Toolbar : public QtManagedToolBar
{
public:
    Toolbar(QWidget *parent, QString toolbarName):
        QtManagedToolBar(parent, toolbarName){}
    void contextMenuEvent(QContextMenuEvent *);
};

void Toolbar::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu(this);
    menu->addAction(tr("TestAction"));
    menu->addAction(tr("TestAction2"));
    menu->addSeparator();

    showContextMenu(event, menu);

    delete menu;
}




int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Wolverine");


    ConsoleAppender *consoleAppender = new ConsoleAppender();
    consoleAppender->setFormat("%t{yyyy-MM-dd mm:ss} [%-7L] %F %i <%C> %m\n");
    FileAppender *fileAppender = new FileAppender("log.log");
    fileAppender->setFormat("%t{yyyy-MM-dd mm:ss} [%-7L] %F %i <%C> %m\n");
    Logger::registerAppender(consoleAppender);
    Logger::registerAppender(fileAppender);

    consoleAppender->setDetailsLevel(Logger::Error);
    LOG_INFO("Starting the application");
    LOG_DEBUG("Starting ");
    LOG_TRACE("Starting the application");
    LOG_WARNING("Starting ");
    //LOG_FATAL("Starting the application");
    LOG_ERROR("Starting ");

    QtActionManager *amanager = QtActionManager::instance();
    amanager->setCurrentScheme("Default");


    CfgAppSettings *settings = CfgAppSettings::instance();
    settings->loadConfiguration();

    settings->createConfigurationBackup();
    settings->general.setValBool(!settings->general.getValBool());
    settings->restoreConfigurationBackup();

    QMainWindow mainWin;
    mainWin.resize(800, 600);
    Toolbar *toolbar = new Toolbar(&mainWin, "MainToolbar");
    QAction *action2 = new QAction("Cut", &mainWin);
    action2->setIcon(QIcon(":/cut.png"));
    toolbar->addAction(action2);

    action2->setShortcut(QKeySequence::Print);
    amanager->addAction(action2);

    QAction *action1 = new QAction("Find", &mainWin);
    action1->setIcon(QIcon(":/find.png"));
    toolbar->addAction(action1);

    action1->setShortcut(QKeySequence("Ctrl+Shift+End"));
    amanager->addAction(action1);

    action1 = new QAction("Paste", &mainWin);
    action1->setIcon(QIcon(":/paste.png"));
    toolbar->addAction(action1);

    amanager->addAction("New", action1);
    amanager->setCurrentScheme("FakeVim");

    QSpinBox *spin = new QSpinBox(toolbar);
    action1 = toolbar->addWidget(spin);
    action1->setText("SpinBox");

    toolbar->restoreConfig();
    toolbar->saveConfig();

    amanager->setCurrentScheme("Nowa");
    amanager->restoreConfig();
    amanager->createConfigurationBackup();

    mainWin.addToolBar(toolbar);
    //toolbar->setManagerEnabled(false);

    Wolverine::DlgSettings *set = new Wolverine::DlgSettings(settings, &mainWin);
    set->showDialog();
    amanager->saveConfig();

    mainWin.show();
    settings->saveConfiguration();
    return app.exec();
}
