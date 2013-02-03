
#include "CfgScintillaSettings.h"

#include <QTextCodec>


ScintillaSettings::ScintillaSettings()
{
    mShowLineNumbersEnabled = true;

    foreach(const QByteArray &name, QTextCodec::availableCodecs()) {
        mCodecAvailable.append(QString(name));
    }
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



void ScintillaSettings::setCodecAvailable(const QStringList &codecs)
{
    mCodecAvailable = codecs;
}
const QStringList& ScintillaSettings::getCodecAvailable()
{
    return mCodecAvailable;
}
void ScintillaSettings::addCodecAvailable(const QString &codec)
{
    mCodecAvailable.append(codec);
    mCodecAvailable.removeDuplicates();
    mCodecAvailable.sort();
}
void ScintillaSettings::delCodecAvailable(const QString &codec)
{
    mCodecAvailable.removeAll(codec);
}
