
#ifndef __QT_MANAGED_TOOLBAR_H_
 #define __QT_MANAGED_TOOLBAR_H_


class QMenu;
class QString;

#include <QMap>
#include <QToolBar>


class QtManagedToolBar : public QToolBar
{
    Q_OBJECT
    Q_PROPERTY(bool     managerEnabled      READ isManagerEnabled       WRITE setManagerEnabled     )


public:
    explicit QtManagedToolBar(QWidget *parent = 0);
    explicit QtManagedToolBar(QWidget *parent, const QString &toolbarName);


    void addAction(const QString &name, QAction *action);
    QAction *addWidget(const QString &name, QWidget *widget);
    void removeAction(QAction *action);
    void removeAction(const QString &name);

     //Provide default context menu
    void contextMenuEvent(QContextMenuEvent *);

     //Property getters
    bool isManagerEnabled() { return mIsManagerEnabled; }

     //Misc
    void saveConfig();
    void restoreConfig();



public slots:
    //Property setters
    void setManagerEnabled(bool val) { mIsManagerEnabled = val; }



protected:
    void showContextMenu(QContextMenuEvent *event, QMenu *menu);
    void saveConfig(const QStringList &actionList);



private slots:
    void showManagerDialog();



private:
     //Private methods
    void init(const QString &name);

    void addActionAvailable(const QString &name, QAction *action);
    QAction* getActionAvailable(const QString &name);

    void applyConfiguration(const QStringList &config);
    QStringList createConfiguration();

     //Private fields
    bool mIsManagerEnabled;
    QString mToolbarName;
    QMap<QString, QAction*> mActionsAvailable;
};

#endif //__QT_MANAGED_TOOLBAR_H_
