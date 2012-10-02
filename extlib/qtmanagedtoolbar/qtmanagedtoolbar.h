
#ifndef __QT_MANAGED_TOOLBAR_H_
 #define __QT_MANAGED_TOOLBAR_H_


#include <QToolBar>

class QtManagedToolBar : public QToolBar
{
    Q_OBJECT
    Q_PROPERTY(bool     managerEnabled      READ isManagerEnabled       WRITE setManagerEnabled     )


public:
    explicit QtManagedToolBar(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *);

    //QWidget
    void addAction(QAction *action);
    void addActions(QList<QAction*> actions);
    void insertAction(QAction *before, QAction *action);
    void insertActions(QAction *before, QList<QAction*> actions);
    void removeAction(QAction *action);

    //QToolBar
    QAction *addAction(const QString &text);
    QAction *addAction(const QIcon &icon, const QString &text);
    QAction *addAction(const QString &text, const QObject *receiver, const char* member);
    QAction *addAction(const QIcon &icon, const QString &text, const QObject *receiver, const char* member);


    bool isManagerEnabled() { return m_isManagerEnabled; }


public slots:
    void setManagerEnabled(bool val) { m_isManagerEnabled = val; }

private slots:
    void showManagerDialog();

private:
    bool m_isManagerEnabled;
    QList<QAction*> m_actionsAvailable;
    QList<QAction*> m_actionsVisible;
};

#endif //__QT_MANAGED_TOOLBAR_H_
