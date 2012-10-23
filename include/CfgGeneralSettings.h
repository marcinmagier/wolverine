
#ifndef __CFG_GENERAL_SETTINGS_H_
 #define __CFG_GENERAL_SETTINGS_H_

#include <QObject>
#include <QString>

class CfgGeneralSettings : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int		valInt		READ getValInt		WRITE setValInt)
	Q_PROPERTY(bool		valBool		READ getValBool		WRITE setValBool)
	Q_PROPERTY(QString	valString	READ getValString	WRITE setValString)

public:
	int getValInt() {return m_valInt;}
	bool getValBool() {return m_valBool;}
	QString getValString() {return m_valString;}


public slots:
    void setValInt(int val) {m_valInt = val;}
    void setValBool(bool val) {m_valBool = val;}
    void setValString(QString val) {m_valString = val;}


private:
	int m_valInt;
	bool m_valBool;
	QString m_valString;
};

#endif //__CFG_GENERAL_SETTINGS_H_
