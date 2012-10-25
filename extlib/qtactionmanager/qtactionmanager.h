
#ifndef __QT_ACTION_MANAGER_H_
 #define __QT_ACTION_MANAGER_H_


class QAction;
class QString;
class QWidget;
class QtActionManagerWidget;


#include <QMap>


typedef QMap<QString, QAction *> QMapActionName;
typedef QMap<QString, QMapActionName> QMapActionGroupName;

typedef QMap<QString, QString> QMapBindingName;
typedef QMap<QString, QMapBindingName> QMapBindingGroupName;
typedef QMap<QString, QMapBindingGroupName> QMapBindingSchemeName;


class QtActionManager
{

private:
    QtActionManager() {}

public:
    static QtActionManager* instance();

    void addAction(QAction *action);
    void addAction(const QString &group, QAction *action);
    //void removeAction(const QString &name);
    //void removeAction(const QString &group, const QString &name);
    //void removeAll(const QString &name);

    void saveConfig();
    void restoreConfig();
    void createConfigurationBackup();
    void restoreConfigurationBackup();
    void dropConfigurationBackup();

    void setCurrentScheme(const QString &name);

    QWidget* getActionManagerWidget(QWidget *parent = 0);


protected:
    void createScheme(const QString &name);


private:
    static QtActionManager* s_actionManager;
    QMapActionGroupName m_actionGroups;
    QMapBindingSchemeName m_actionSchemes;

    friend class QtActionManagerWidget;
};

#endif // __QT_ACTION_MANAGER_H_
