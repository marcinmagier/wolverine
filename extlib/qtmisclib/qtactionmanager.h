/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtactionmanager.h
 *  @brief      QtActionManager class interface.
 */

#ifndef __QT_ACTION_MANAGER_H_
 #define __QT_ACTION_MANAGER_H_


class QAction;
class QString;
class QWidget;

namespace Impl {
class QtActionManager;
}



class QtActionManager
{
public:
    explicit QtActionManager();
    ~QtActionManager();

    void addAction(const QString &group, const QString &name, QAction *action);
    QAction* getAction(const QString &group, const QString &name);

    void saveConfig();
    void restoreConfig();
    void createConfigurationBackup();
    void restoreConfigurationBackup();
    void dropConfigurationBackup();

    void addScheme(const QString &name);
    void setScheme(const QString &name);
    QString getScheme();

    QWidget* getActionManagerWidget(QWidget *parent = 0);


private:
    Impl::QtActionManager* mActionManagerImpl;
    Impl::QtActionManager* mActionManagerImplBackup;
};

#endif // __QT_ACTION_MANAGER_H_
