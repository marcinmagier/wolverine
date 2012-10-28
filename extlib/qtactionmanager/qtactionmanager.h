
#ifndef __QT_ACTION_MANAGER_H_
 #define __QT_ACTION_MANAGER_H_


class QAction;
class QWidget;
class QtAction;
class QtActionManagerWidget;


#include <QMap>
#include <QString>



typedef QList<QtAction*> QtActionsList;
typedef QMap<QString, QtActionsList> QtActionCategoryMap;



class QtActionManager
{

private:
    explicit QtActionManager();


public:
    ~QtActionManager();
    static QtActionManager* instance();

    void addAction(QAction *action);
    void addAction(const QString &group, QAction *action);

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
    QString m_currentScheme;
    QList<QString> m_schemes;
    QtActionCategoryMap m_actionCategories;

    friend class QtActionManagerWidget;
};

#endif // __QT_ACTION_MANAGER_H_
