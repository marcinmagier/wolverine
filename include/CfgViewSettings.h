
#ifndef __CFG_VIEW_SETTINGS_H_
 #define __CFG_VIEW_SETTINGS_H_

#include <QObject>
#include <QString>
#include <QColor>

class ViewSettings : public QObject
{
	Q_OBJECT

    Q_PROPERTY(int		popupTimeout        READ getPopupTimeout        WRITE setPopupTimeout       )
    Q_PROPERTY(QString	popupAnimationType	READ getPopupAnimationType	WRITE setPopupAnimationType )
    Q_PROPERTY(QColor   popupBgColor        READ getPopupBgColor        WRITE setPopupBgColor       )
    Q_PROPERTY(QColor   popupFgColor        READ getPopupFgColor        WRITE setPopupFgColor       )


public:
    explicit ViewSettings();

    int getPopupTimeout();
    QString getPopupAnimationType();
    QColor getPopupBgColor();
    QColor getPopupFgColor();


signals:
    void popupTimeoutChanged(int val);
    void popupAnimationTypeChanged(QString val);
    void popupBgColorChanged(QColor val);
    void popupFgColorChanged(QColor val);


public slots:
    void setPopupTimeout(int val);
    void setPopupAnimationType(QString val);
    void setPopupBgColor(QColor val);
    void setPopupFgColor(QColor val);


private:
    int mPopupTimeout;
    QString mPopupAnimationType;
    QColor mPopupBgColor;
    QColor mPopupFgColor;
};



#endif //__CFG_VIEW_SETTINGS_H_
