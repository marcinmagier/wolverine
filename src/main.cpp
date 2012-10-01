
#include "AppConfig.h"
#include <QApplication>
#include <QMainWindow>



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Wolverine");

    AppConfig *settings = AppConfig::instance();
    settings->loadConfiguration();
    settings->saveConfiguration();

    QMainWindow mainWin;
    mainWin.resize(800, 600);
    mainWin.show();
    return app.exec();
}
