
#include "WApplication.h"
#include "WMainWindow.h"


#include <QApplication>

#include <QtGui>
#include <QObject>




int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Wolverine::Application *application = Wolverine::Application::instance();
    Wolverine::MainWindow *mainWindow = new Wolverine::MainWindow();

    mainWindow->show();

    int ret = app.exec();
    delete mainWindow;
    delete application;
    return ret;
}
