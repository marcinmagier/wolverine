

#ifndef __W_ACTION_MANAGER_H_
 #define __W_ACTION_MANAGER_H_


#include "qtactionmanager.h"

#include <QObject>



namespace Wolverine
{

class ActionManager : public QObject, public QtActionManager
{
    Q_OBJECT

public:
    explicit ActionManager(QObject *parent = 0);
    
signals:
    
public slots:
    
};


}



#define W_ACTION_GROUP_FILE     "File"




#define W_ACTION_NEW            "New"




#endif // __W_ACTION_MANAGER_H_
