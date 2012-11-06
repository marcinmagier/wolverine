
#include "CfgHiddenSettings.h"


HiddenSettings::HiddenSettings()
{
    m_mwPosition = QPoint(100, 100);
    m_mwSize = QSize(500, 400);
}


void HiddenSettings::setMWPosition(QPoint val)
{
    if(m_mwPosition != val) {
        m_mwPosition = val;
        emit mwPositionChanged(val);
    }
}


void HiddenSettings::setMWSize(QSize val)
{
    if(m_mwSize != val) {
        m_mwSize = val;
        emit mwSizeChanged(val);
    }
}
