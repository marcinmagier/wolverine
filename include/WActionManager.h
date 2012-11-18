

#ifndef __W_ACTION_MANAGER_H_
 #define __W_ACTION_MANAGER_H_

class QMainWindow;

#include "qtactionmanager.h"

#include <QObject>



namespace Wolverine
{

class ActionManager : public QObject, public QtActionManager
{
    Q_OBJECT

public:
    explicit ActionManager(QMainWindow *mainWindow);
    
signals:
    
public slots:

private:
    QMainWindow *mMainWindow;
    
};


}

#endif // __W_ACTION_MANAGER_H_
