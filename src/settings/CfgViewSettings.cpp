
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

}


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
