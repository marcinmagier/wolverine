/**************************************************************************************************
**
** Copyright (C) 2012 Magier Marcin.
**
**
**************************************************************************************************/



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

    void saveConfig();
    void restoreConfig();

    bool isManagerEnabled() { return mIsManagerEnabled; }

    //Provide default context menu
   void contextMenuEvent(QContextMenuEvent *);

public slots:
    void setManagerEnabled(bool val) { mIsManagerEnabled = val; }



protected:
    void saveConfig(const QStringList &actionNames);
    void showContextMenu(QContextMenuEvent *event, QMenu *menu);



private slots:
    void showManagerDialog();

private:
    void init(const QString &name);

    void addActionAvailable(const QString &name, QAction *action);
    void applyConfiguration(const QStringList &actionNames);
    QStringList createConfiguration();


    bool mIsManagerEnabled;
    QString mToolbarName;
    QMap<QString, QAction*> mActionsAvailable;
};

#endif //__QT_MANAGED_TOOLBAR_H_
