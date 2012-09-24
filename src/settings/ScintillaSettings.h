
#include <QObject>
#include <QString>
#include <QSettings>

class ScintillaSettings : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int		valInt		READ getValInt		WRITE setValInt)
	Q_PROPERTY(bool		valBool		READ getValBool		WRITE setValBool)
	Q_PROPERTY(QString	valString	READ getValString	WRITE setValString)

public:
	// valInt
	int getValInt() {return m_valInt;}
	void setValInt(int val) {m_valInt = val;}
	
	// valBool
	bool getValBool() {return m_valBool;}
	void setValBool(bool val) {m_valBool = val;}

	// valString
	QString getValString() {return m_valString;}
	void setValString(QString val) {m_valString = val;}
	
private:
	int m_valInt;
	bool m_valBool;
	QString m_valString;
};
