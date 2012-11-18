

#include "WActionManager.h"

#include <QMainWindow>



using namespace Wolverine;



ActionManager::ActionManager(QMainWindow *mainWindow) :
    QObject(mainWindow), mMainWindow(mainWindow)
{
}
