
#ifndef __QT_ACTION_H_
 #define __QT_ACTION_H_


#include <QMap>
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
    void applyBindingList(const QStringList &list);


    QAction *action;
    QMap<QString, QString> schemeBinding;
};


#endif // __QT_ACTION_H_
