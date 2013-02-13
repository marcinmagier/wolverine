
#include "CfgViewSettings.h"
#include "wolverine_cfg.h"

#include <QApplication>
#include <QPalette>

ViewSettings::ViewSettings()
{
    mPopupTimeout = 5;
    mPopupAnimationType = QString(POPUP_ANIMATION_TYPES).split(" ")[0];
    mPopupBgColor = QApplication::palette().color(QPalette::ToolTipBase);
    mPopupFgColor = QApplication::palette().color(QPalette::ToolTipText);


    mTabBarMovable = true;
    mTabBarCloseVisible = true;
    mTabBarDoubleClkClose = true;
    mTabBarDoubleClkNew = true;
    mTabBarMiddleBtnClose = true;
    mTabBarMiddleBtnNew = true;
    mTabBarModernStyleEnabled = true;
}




//=======================  Popup  ===========================================//

void ViewSettings::setPopupTimeout(int val)
{
    if(mPopupTimeout != val) {
        mPopupTimeout = val;
        emit popupTimeoutChanged(mPopupTimeout);
    }
}

void ViewSettings::setPopupAnimationType(QString val)
{
    if(mPopupAnimationType != val) {
        mPopupAnimationType = val;
        emit popupAnimationTypeChanged(mPopupAnimationType);
    }
}

void ViewSettings::setPopupBgColor(QColor val)
{
    if(mPopupBgColor != val) {
        mPopupBgColor = val;
        emit popupBgColorChanged(mPopupBgColor);
    }
}

void ViewSettings::setPopupFgColor(QColor val)
{
    if(mPopupFgColor != val) {
        mPopupFgColor = val;
        emit popupFgColorChanged(mPopupFgColor);
    }
}


int ViewSettings::getPopupTimeout()
{
    return mPopupTimeout;
}

QString ViewSettings::getPopupAnimationType()
{
    return mPopupAnimationType;
}

QColor ViewSettings::getPopupBgColor()
{
    return mPopupBgColor;
}

QColor ViewSettings::getPopupFgColor()
{
    return mPopupFgColor;
}



//=======================  TabBar  ==========================================//

void ViewSettings::setTabBarMovable(bool val)
{
    if(mTabBarMovable != val) {
        mTabBarMovable = val;
        emit tabBarMovableChanged(mTabBarMovable);
    }
}
bool ViewSettings::isTabBarMovable()
{
    return mTabBarMovable;
}

void ViewSettings::setTabBarCloseVisible(bool val)
{
    if(mTabBarCloseVisible != val) {
        mTabBarCloseVisible = val;
        emit tabBarCloseVisibleChanged(mTabBarCloseVisible);
    }
}
bool ViewSettings::isTabBarCloseVisible()
{
    return mTabBarCloseVisible;
}

void ViewSettings::setTabBarDoubleClkClose(bool val)
{
    if(mTabBarDoubleClkClose != val) {
        mTabBarDoubleClkClose = val;
        emit tabBarDoubleClkCloseChanged(mTabBarDoubleClkClose);
    }
}
bool ViewSettings::isTabBarDoubleClkClose()
{
    return mTabBarDoubleClkClose;
}

void ViewSettings::setTabBarDoubleClkNew(bool val)
{
    if(mTabBarDoubleClkNew != val) {
        mTabBarDoubleClkNew = val;
        emit tabBarDoubleClkCloseChanged(mTabBarDoubleClkNew);
    }
}
bool ViewSettings::isTabBarDoubleClkNew()
{
    return mTabBarDoubleClkNew;
}

void ViewSettings::setTabBarMiddleBtnClose(bool val)
{
    if(mTabBarMiddleBtnClose != val) {
        mTabBarMiddleBtnClose = val;
        emit tabBarMiddleBtnCloseChanged(mTabBarMiddleBtnClose);
    }
}
bool ViewSettings::isTabBarMiddleBtnClose()
{
    return mTabBarMiddleBtnClose;
}

void ViewSettings::setTabBarMiddleBtnNew(bool val)
{
    if(mTabBarMiddleBtnNew != val) {
        mTabBarMiddleBtnNew = val;
        emit tabBarMiddleBtnCloseChanged(mTabBarMiddleBtnNew);
    }
}
bool ViewSettings::isTabBarMiddleBtnNew()
{
    return mTabBarMiddleBtnNew;
}

void ViewSettings::setTabBarModernStyleEnabled(bool val)
{
    if(mTabBarModernStyleEnabled != val) {
        mTabBarModernStyleEnabled = val;
        emit tabBarModernStyleEnabledChanged(mTabBarModernStyleEnabled);
    }
}
bool ViewSettings::isTabBarModernStyleEnabled()
{
    return mTabBarModernStyleEnabled;
}


