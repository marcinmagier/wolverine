
#ifndef __CFG_VOLATILE_SETTINGS_H_
 #define __CFG_VOLATILE_SETTINGS_H_

#include <QObject>
#include <QString>


class DynamicSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString      dataDir             READ getDataDir           )
    Q_PROPERTY(QString      instalDir           READ getInstalDir         )
    Q_PROPERTY(QString      pluginsDir          READ getPluginsDir        )
    Q_PROPERTY(QString      translationsDir     READ getTranslationsDir   )



public:
    explicit DynamicSettings();

    QString getDataDir() {return mDataDir;}
    QString getInstalDir() {return mInstalDir;}
    QString getPluginsDir();
    QString getTranslationsDir();
	


signals:



public slots:



private:
    QString mDataDir;
    QString mInstalDir;
};

#endif //__CFG_VOLATILE_SETTINGS_H_
