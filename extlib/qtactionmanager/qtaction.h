
#ifndef __QT_ACTION_H_
 #define __QT_ACTION_H_


class QAction;


#include <QMap>
#include <QString>



class QtAction
{
public:
    explicit QtAction(QAction *action);
    explicit QtAction(const QtAction &other);

    QtAction& operator=(const QtAction &other);

    QString shortcut(QString scheme);


    QAction *action;
    QMap<QString, QString> schemeBinding;
};


#endif // __QT_ACTION_H_
