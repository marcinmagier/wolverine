/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       qtaction.h
 *  @brief      QtAction class interface.
 *  @details    It shouldn't be used outside qtactionmanager library.
 */


#ifndef __QT_ACTION_H_
 #define __QT_ACTION_H_


#include <QHash>
#include <QString>
#include <QObject>
#include <QAction>



class QtAction
{
public:
    explicit QtAction();
    explicit QtAction(QAction *action);
    explicit QtAction(const QtAction &other);
    ~QtAction() {}

    QtAction& operator=(const QtAction &other);

    QString shortcut(QString scheme);
    QStringList createBindingList();
    void applyBindingList(const QStringList &schemes, const QStringList &list);


    QAction *action;
    QHash<QString, QString> schemeBinding;
};


#endif // __QT_ACTION_H_
