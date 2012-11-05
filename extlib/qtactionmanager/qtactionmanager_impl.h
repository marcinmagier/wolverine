#ifndef __QT_ACTION_MANAGER_PRV_H_
 #define __QT_ACTION_MANAGER_PRV_H_


class QAction;
class QWidget;
class QtAction;


#include <QMap>
#include <QString>


typedef QList<QtAction*> QtActionsList;
typedef QMap<QString, QtActionsList> QtActionCategoryMap;



namespace Impl {


class QtActionManager
{

public:
    explicit QtActionManager();
    explicit QtActionManager(const QtActionManager &other);
    ~QtActionManager();

    void addAction(const QString &group, QAction *action);

    void saveConfig();
    void restoreConfig();

    void setCurrentScheme(const QString &name);

    QString m_currentScheme;
    QList<QString> m_schemes;
    QtActionCategoryMap m_actionCategories;
};

}



#endif // __QT_ACTION_MANAGER_PRV_H_
