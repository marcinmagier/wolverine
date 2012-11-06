
#ifndef __CFG_HIDDEN_SETTINGS_H_
 #define __CFG_HIDDEN_SETTINGS_H_

#include <QObject>
#include <QString>
#include <QPoint>
#include <QSize>


class HiddenSettings : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QPoint       mwPosition      READ getMWPosition		WRITE setMWPosition)
    Q_PROPERTY(QSize		mwSize          READ getMWSize            WRITE setMWSize)



public:
    explicit HiddenSettings();

    QPoint getMWPosition() {return m_mwPosition;}
    QSize getMWSize() {return m_mwSize;}


signals:
    void mwPositionChanged(QPoint val);
    void mwSizeChanged(QSize val);


public slots:
    void setMWPosition(QPoint val);
    void setMWSize(QSize val);

	
private:
    QPoint m_mwPosition;
    QSize m_mwSize;
};

#endif //__CFG_HIDDEN_SETTINGS_H_
