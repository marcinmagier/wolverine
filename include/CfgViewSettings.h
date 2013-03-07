
#ifndef __CFG_VIEW_SETTINGS_H_
 #define __CFG_VIEW_SETTINGS_H_

#include <QObject>
#include <QString>
#include <QColor>

class ViewSettings : public QObject
{
	Q_OBJECT

    Q_PROPERTY(int		popupTimeout                READ getPopupTimeout                WRITE setPopupTimeout               )
    Q_PROPERTY(QString	popupAnimationType          READ getPopupAnimationType          WRITE setPopupAnimationType         )
    Q_PROPERTY(QColor   popupBgColor                READ getPopupBgColor                WRITE setPopupBgColor               )
    Q_PROPERTY(QColor   popupFgColor                READ getPopupFgColor                WRITE setPopupFgColor               )

    Q_PROPERTY(bool     tabBarMovable               READ isTabBarMovable                WRITE setTabBarMovable              )
    Q_PROPERTY(bool     tabBarCloseVisible          READ isTabBarCloseVisible           WRITE setTabBarCloseVisible         )
    Q_PROPERTY(bool     tabBarDoubleClkClose        READ isTabBarDoubleClkClose         WRITE setTabBarDoubleClkClose       )
    Q_PROPERTY(bool     tabBarDoubleClkNew          READ isTabBarDoubleClkNew           WRITE setTabBarDoubleClkNew         )
    Q_PROPERTY(bool     tabBarMiddleBtnClose        READ isTabBarMiddleBtnClose         WRITE setTabBarMiddleBtnClose       )
    Q_PROPERTY(bool     tabBarMiddleBtnNew          READ isTabBarMiddleBtnNew           WRITE setTabBarMiddleBtnNew         )
    Q_PROPERTY(bool     tabBarModernStyleEnabled    READ isTabBarModernStyleEnabled     WRITE setTabBarModernStyleEnabled   )
    Q_PROPERTY(QColor   tabBarActiveBgColor         READ getTabBarActiveBgColor         WRITE setTabBarActiveBgColor        )



public:
    explicit ViewSettings();

    int getPopupTimeout();
    QString getPopupAnimationType();
    QColor getPopupBgColor();
    QColor getPopupFgColor();

    bool isTabBarMovable();
    bool isTabBarCloseVisible();
    bool isTabBarDoubleClkClose();
    bool isTabBarDoubleClkNew();
    bool isTabBarMiddleBtnClose();
    bool isTabBarMiddleBtnNew();
    bool isTabBarModernStyleEnabled();
    QColor getTabBarActiveBgColor();



signals:
    void popupTimeoutChanged(int val);
    void popupAnimationTypeChanged(QString val);
    void popupBgColorChanged(QColor val);
    void popupFgColorChanged(QColor val);

    void tabBarMovableChanged(bool val);
    void tabBarCloseVisibleChanged(bool val);
    void tabBarDoubleClkCloseChanged(bool val);
    void tabBarDoubleClkCloseNew(bool val);
    void tabBarMiddleBtnCloseChanged(bool val);
    void tabBarMiddleBtnCloseNew(bool val);
    void tabBarModernStyleEnabledChanged(bool val);
    void tabBarActiveBgColorChanged(const QColor &color);



public slots:
    void setPopupTimeout(int val);
    void setPopupAnimationType(QString val);
    void setPopupBgColor(QColor val);
    void setPopupFgColor(QColor val);

    void setTabBarMovable(bool val);
    void setTabBarCloseVisible(bool val);
    void setTabBarDoubleClkClose(bool val);
    void setTabBarDoubleClkNew(bool val);
    void setTabBarMiddleBtnClose(bool val);
    void setTabBarMiddleBtnNew(bool val);
    void setTabBarModernStyleEnabled(bool val);
    void setTabBarActiveBgColor(const QColor &val);


private:
    int mPopupTimeout;
    QString mPopupAnimationType;
    QColor mPopupBgColor;
    QColor mPopupFgColor;

    bool mTabBarMovable;
    bool mTabBarCloseVisible;
    bool mTabBarDoubleClkClose;
    bool mTabBarDoubleClkNew;
    bool mTabBarMiddleBtnClose;
    bool mTabBarMiddleBtnNew;
    bool mTabBarModernStyleEnabled;
    QColor mTabBarActiveBgColor;
};



#endif //__CFG_VIEW_SETTINGS_H_
