

#include "WMainWindow.h"


#include <QApplication>

#include <QtGui>
#include <QObject>




int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Wolverine");

    Wolverine::MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
