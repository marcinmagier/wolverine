
#ifndef __QT_ACTION_MANAGER_H_
 #define __QT_ACTION_MANAGER_H_


class QAction;
//class QString;
class QWidget;
class QtActionManagerWidget;


#include <QMap>
#include <QString>



class QtAction
{
public:
    explicit QtAction(QAction *action);
    explicit QtAction(const QtAction &other);

    QtAction& operator =(const QtAction &other);


    QAction *action;
    QMap<QString, QString> schemeBinding;
};


typedef QList<QtAction> QListQtActions;
typedef QMap<QString, QListQtActions> QMapActionCategory;



class QtActionManager
{

private:
    explicit QtActionManager();

public:
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
    QMapActionCategory m_actionCategories;

    friend class QtActionManagerWidget;
};

#endif // __QT_ACTION_MANAGER_H_
