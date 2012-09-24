
#include <QObject>
#include <QSettings>

class Settings
{

public:
	virtual bool readSettings() = 0;
	virtual bool writeSettings() = 0;

protected:
    void readGroup(QSettings &qset, QObject *qobj);
    void writeGroup(QSettings &qset, QObject *qobj);

};