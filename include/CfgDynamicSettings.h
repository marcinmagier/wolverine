
#ifndef __CFG_VOLATILE_SETTINGS_H_
 #define __CFG_VOLATILE_SETTINGS_H_

#include <QObject>
#include <QString>


class DynamicSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString      instalDir       READ getInstalDir         )
    Q_PROPERTY(QString      dataDir         READ getDataDir           )



public:
    explicit DynamicSettings();

    QString getInstalDir() {return mInstalDir;}
    QString getDataDir() {return mDataDir;}
	


signals:



public slots:



private:
    QString mInstalDir;
    QString mDataDir;
};

#endif //__CFG_VOLATILE_SETTINGS_H_
