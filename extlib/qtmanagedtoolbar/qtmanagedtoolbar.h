
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
    QtManagedToolBar(QWidget *parent = 0, QString toolbarName = "NoNameToolbar");

    void contextMenuEvent(QContextMenuEvent *);

    bool isManagerEnabled() { return m_isManagerEnabled; }
    void restoreConfig();
    void saveConfig();
    void saveConfig(QStringList &actionList);


public slots:
    void setManagerEnabled(bool val) { m_isManagerEnabled = val; }


protected:
    void showContextMenu(QContextMenuEvent *event, QMenu *menu);


private slots:
    void showManagerDialog();


private:
    QAction* getActionAvailableFromString(const QString &name);
    void findActionsAvailable();
    void applyConfiguration(const QStringList &config);
    QStringList createConfiguration();

    bool m_isManagerEnabled;
    QString m_toolbarName;
    QList<QAction*> m_actionsAvailable;
};

#endif //__QT_MANAGED_TOOLBAR_H_
