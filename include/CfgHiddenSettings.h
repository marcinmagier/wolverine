
#ifndef __CFG_HIDDEN_SETTINGS_H_
 #define __CFG_HIDDEN_SETTINGS_H_

#include <QObject>
#include <QString>
#include <QPoint>
#include <QSize>


class CfgHiddenSettings : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QPoint       windowPosition	READ getPosition		WRITE setPosition)
    Q_PROPERTY(QSize		windowSize		READ getSize            WRITE setSize)



public:

    // position
    QPoint getPosition() {return m_position;}
    void setPosition(QPoint val) {m_position = val;}

    // size
    QSize getSize() {return m_size;}
    void setSize(QSize val) {m_size = val;}
	
private:
    QPoint m_position;
    QSize m_size;
};

#endif //__CFG_HIDDEN_SETTINGS_H_