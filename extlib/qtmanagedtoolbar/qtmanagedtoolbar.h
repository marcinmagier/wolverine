
#ifndef __QT_MANAGED_TOOLBAR_H_
 #define __QT_MANAGED_TOOLBAR_H_


#include <QToolBar>

class QMenu;
class QString;

class QtManagedToolBar : public QToolBar
{
    Q_OBJECT
    Q_PROPERTY(bool     managerEnabled      READ isManagerEnabled       WRITE setManagerEnabled     )


public:
    explicit QtManagedToolBar(QWidget *parent = 0);
    explicit QtManagedToolBar(QWidget *parent, const QString &toolbarName);

     //Redefine QToolBar's methods related to QAction
    void addAction(QAction *action);
    QAction *addAction(const QString &text);
    QAction *addAction(const QIcon &icon, const QString &text);
    QAction *addAction(const QString &text, const QObject *receiver, const char* member);
    QAction *addAction(const QIcon &icon, const QString &text, const QObject *receiver, const char* member);

    QAction *addWidget(QWidget *widget);
    QAction *insertWidget(QAction *before, QWidget *widget);

     //Redefine QWidget's methods related to QAction
    void addActions(QList<QAction*> actions);
    void insertAction(QAction *before, QAction *action);
    void insertActions(QAction *before, QList<QAction*> actions);
    void removeAction(QAction *action);

     //Provide default context menu
    void contextMenuEvent(QContextMenuEvent *);

     //Property getters
    bool isManagerEnabled() { return m_isManagerEnabled; }

     //Misc
    void saveConfig();
    void restoreConfig();



public slots:
    //Property setters
    void setManagerEnabled(bool val) { m_isManagerEnabled = val; }



protected:
    void showContextMenu(QContextMenuEvent *event, QMenu *menu);
    void saveConfig(const QStringList &actionList);



private slots:
    void showManagerDialog();



private:
     //Private methods
    void init(const QString &name);

    void addActionAvailable(QAction *action);
    void addActionsAvailable(QList<QAction*> actions);
    QAction* getActionAvailable(const QString &name);

    void applyConfiguration(const QStringList &config);
    QStringList createConfiguration();

     //Private fields
    bool m_isManagerEnabled;
    QString m_toolbarName;
    QList<QAction*> m_actionsAvailable;
};

#endif //__QT_MANAGED_TOOLBAR_H_
