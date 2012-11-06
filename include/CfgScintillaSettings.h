
#ifndef __CFG_SCINTILLA_SETTINGS_H_
 #define __CFG_SCINTILLA_SETTINGS_H_

#include <QObject>
#include <QString>

class ScintillaSettings : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int		valInt		READ getValInt		WRITE setValInt)
	Q_PROPERTY(bool		valBool		READ getValBool		WRITE setValBool)
	Q_PROPERTY(QString	valString	READ getValString	WRITE setValString)

public:
    explicit ScintillaSettings();

	int getValInt() {return m_valInt;}
	bool getValBool() {return m_valBool;}
	QString getValString() {return m_valString;}


signals:
    void valBoolChanged(bool val);
    void valIntChanged(int val);
    void valStringChanged(QString val);


public slots:
    void setValInt(int val) {
        if(val != m_valInt)
            emit valIntChanged(val);
        m_valInt = val;
    }
    void setValBool(bool val) {
        if(val != m_valBool)
            emit valBoolChanged(val);
        m_valBool = val;
    }
    void setValString(QString val) {
        if(val !=m_valString)
            emit valStringChanged(val);
        m_valString = val;
    }


private:
	int m_valInt;
	bool m_valBool;
	QString m_valString;
};

#endif //__CFG_SCINTILLA_SETTINGS_H_
