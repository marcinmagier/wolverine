/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtactionmanager_impl.h
 *  @brief      Impl::QtActionManager class interface.
 *  @details    It shouldn't be used outside qtactionmanager library.
 */


#ifndef __QT_ACTION_MANAGER_PRV_H_
 #define __QT_ACTION_MANAGER_PRV_H_


class QAction;
class QWidget;
class QtAction;


#include <QMap>
#include <QString>


typedef QMap<QString, QtAction*> QtActionsMap;
typedef QMap<QString, QtActionsMap> QtActionCategoryMap;



namespace Impl {


class QtActionManager
{

public:
    explicit QtActionManager();
    explicit QtActionManager(const QtActionManager &other);
    ~QtActionManager();

    void addAction(const QString &group, const QString &name, QAction *action);
    QAction* getAction(const QString &group, const QString &name);

    void saveConfig();
    void restoreConfig();

    void addBuiltinScheme(const QString &name);
    void addUserScheme(const QString &name);
    void removeUserScheme(const QString &name);
    void setCurrentScheme(const QString &name);
    QString getCurrentScheme();

    QString mCurrentScheme;
    QList<QString> mSchemes;
    QList<QString> mUserSchemes;
    QtActionCategoryMap mActionCategories;
};

}



#endif // __QT_ACTION_MANAGER_PRV_H_
