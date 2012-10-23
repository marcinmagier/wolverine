
#ifndef __QT_CONFIG_H_
 #define __QT_CONFIG_H_


class QObject;
class QSettings;

class QtConfig
{

public:
    virtual ~QtConfig() {}

    virtual bool loadConfiguration() = 0;
    virtual bool saveConfiguration() = 0;
    virtual void createConfigurationBackup() = 0;
    virtual void restoreConfigurationBackup() = 0;
    virtual void dropConfigurationBackup() =0;

protected:
    void loadGroup(QSettings &qset, QObject *qobj);
    void saveGroup(QSettings &qset, QObject *qobj);

    void copyGroup(QObject *to, const QObject *from);

};

#endif //__QT_CONFIG_H_
