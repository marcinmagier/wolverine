#ifndef __QT_ACTION_MANAGER_H_
  #define __QT_ACTION_MANAGER_H_

#include <QMap>
#include <QAction>
#include <QWidget>



class QtActionManager
{
    
public:
    //explicit QtActionManager(){};
   // ~QtActionManager();

    void addAction(QAction *action);
    void addAction(const QString &group, QAction *action);
    void removeAction(const QString &name);
    void removeAction(const QString &group, const QString &name);
    void removeAll(const QString &name);



private:
    typedef QMap<QString, QAction *> QActionMapper;
    QMap<QString, QActionMapper > m_actionGroups;
};

#endif // __QT_ACTION_MANAGER_H_
