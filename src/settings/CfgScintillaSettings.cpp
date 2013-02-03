
#include "CfgScintillaSettings.h"

#include <QTextCodec>


ScintillaSettings::ScintillaSettings()
{
    mShowLineNumbersEnabled = true;

    QList<QByteArray> codecs = QTextCodec::availableCodecs();
    foreach(QByteArray name, codecs) {
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
}
