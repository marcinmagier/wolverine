
#include "AppConfig.h"
#include "qtmanagedtoolbar.h"

#include <QApplication>
#include <QMainWindow>
#include <QtGui>



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Wolverine");

    AppConfig *settings = AppConfig::instance();
    settings->loadConfiguration();
    settings->saveConfiguration();

    QMainWindow mainWin;
    mainWin.resize(800, 600);
    QtManagedToolBar *toolbar = new QtManagedToolBar(&mainWin);
    QAction *action1 = new QAction("Cut", &mainWin);
    action1->setIcon(QIcon(":/cut.png"));
    toolbar->addAction(action1);

    mainWin.addToolBar(toolbar);
    mainWin.show();
    return app.exec();
}
