
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
    QtManagedToolBar(QWidget *parent = 0, QString toolbarName = "Default");

    void contextMenuEvent(QContextMenuEvent *);


    bool isManagerEnabled() { return m_isManagerEnabled; }
    void restoreConfig();


public slots:
    void setManagerEnabled(bool val) { m_isManagerEnabled = val; }

private slots:
    void showManagerDialog();

protected:
    void showContextMenu(QContextMenuEvent *event, QMenu *menu);


public:
    void saveConfig();


private:
    QAction* getActionFromString(const QString &name);
    void findActionsAvailable();
    void applyConfiguration(const QStringList &config);
    QStringList createConfiguration();

private:
    bool m_isManagerEnabled;
    QString m_toolbarName;
    QList<QAction*> m_actionsAvailable;
};

#endif //__QT_MANAGED_TOOLBAR_H_
