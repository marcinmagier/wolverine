
#include "CfgScintillaSettings.h"


ScintillaSettings::ScintillaSettings()
{
    mShowLineNumbersEnabled = true;
}



//======================  General  ==========================================//

void ScintillaSettings::setShowLineNumbersEnabled(bool val)
{
    if(mShowLineNumbersEnabled != val) {
        mShowLineNumbersEnabled = val;
        emit showLineNumbersEnabledChanged(mShowLineNumbersEnabled);
    }
}
bool ScintillaSettings::isShowLineNumbersEnabled()
{
    return mShowLineNumbersEnabled;
}



