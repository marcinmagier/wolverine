
#ifndef __QT_ACTION_MANAGER_H_
 #define __QT_ACTION_MANAGER_H_


class QAction;
class QString;
class QWidget;


#include <QMap>


typedef QMap<QString, QAction *> QActionMapper;


class QtActionManager
{
    
public:
    explicit QtActionManager() {}

    void addAction(QAction *action);
    void addAction(const QString &group, QAction *action);
    void removeAction(const QString &name);
    void removeAction(const QString &group, const QString &name);
    void removeAll(const QString &name);

    QWidget* getActionManagerWidget(QWidget *parent = 0);

private:
    QMap<QString, QActionMapper > m_actionGroups;
};

#endif // __QT_ACTION_MANAGER_H_
