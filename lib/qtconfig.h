
#ifndef __QT_CONFIG_H_
 #define __QT_CONFIG_H_


#include <QObject>
#include <QSettings>

class QtConfig
{

public:
    virtual bool loadConfiguration() = 0;
    virtual bool saveConfiguration() = 0;

protected:
    void loadGroup(QSettings &qset, QObject *qobj);
    void saveGroup(QSettings &qset, QObject *qobj);

};

#endif //__QCONFIG_H_
