
#ifndef __QT_ACTION_MANAGER_H_
 #define __QT_ACTION_MANAGER_H_


class QAction;
class QString;
class QWidget;


namespace Private {
class QtActionManager;
}


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


private:
    static QtActionManager* s_actionManager;

    Private::QtActionManager* m_actionManager;
    Private::QtActionManager* m_actionManagerBackup;
};

#endif // __QT_ACTION_MANAGER_H_
