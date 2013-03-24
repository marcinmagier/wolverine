
#include "CfgScintillaSettings.h"

#include <QTextCodec>


ScintillaSettings::ScintillaSettings()
{
    mShowLineNumbersEnabled = true;

    mEolVisible = false;
    mEolVisiblePriv = false;
    mWhiteSpaceVisible = false;
    mWhiteSpaceVisiblePriv = false;
    mWhiteSpaceVisibleMode = 1; //SCWS_VISIBLEALWAYS
    mShowWhiteCharsEnabled = false;

    mWrapModeEnabled = false;
    mWrapMode = 1;  //SC_WRAP_WORD

    mIndentGuideEnabled = false;

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


void ScintillaSettings::setEolVisible(bool val)
{
    if(mEolVisible != val) {
        mEolVisible = val;
        emit eolVisibleChanged(mEolVisible);
        setShowWhiteCharsEnabled(mEolVisible || mWhiteSpaceVisible);
    }
}
bool ScintillaSettings::isEolVisible()
{
    return mEolVisible;
}

void ScintillaSettings::setWhiteSpaceVisible(bool val)
{
    if(mWhiteSpaceVisible != val) {
        mWhiteSpaceVisible = val;
        emit whiteSpaceVisibleChanged(mWhiteSpaceVisible);
        setShowWhiteCharsEnabled(mEolVisible || mWhiteSpaceVisible);
    }
}
bool ScintillaSettings::isWhiteSpaceVisible()
{
    return mWhiteSpaceVisible;
}

void ScintillaSettings::setWhiteSpaceVisibleMode(int val)
{
    if(mWhiteSpaceVisibleMode != val) {
        mWhiteSpaceVisibleMode = val;
    }
}
int ScintillaSettings::getWhiteSpaceVisibleMode()
{
    return mWhiteSpaceVisibleMode;
}

void ScintillaSettings::setShowWhiteCharsEnabled(bool val)
{
    if(mShowWhiteCharsEnabled != val) {
        mShowWhiteCharsEnabled = val;
        if(val) {
            if(!(mEolVisible || mWhiteSpaceVisible)) {
                //Neither eol nor ws are visible, check previous values.
                if(mEolVisiblePriv) {
                    setEolVisible(true);
                }
                if(mWhiteSpaceVisiblePriv) {
                    setWhiteSpaceVisible(true);
                }
            }
            if(!(mEolVisible || mWhiteSpaceVisible)) {
                //Eol and ws are still not visible, show both.
                setEolVisible(true);
                setWhiteSpaceVisible(true);
            }
        } else {
            mEolVisiblePriv = mEolVisible;
            mWhiteSpaceVisiblePriv = mWhiteSpaceVisible;
            setEolVisible(false);
            setWhiteSpaceVisible(false);
        }
        emit showWhiteCharsEnabledChanged(mShowWhiteCharsEnabled);

    }
}
bool ScintillaSettings::isShowWhiteCharsEnabled()
{
    return mShowWhiteCharsEnabled;
}

void ScintillaSettings::setWrapModeEnabled(bool val)
{
    if(mWrapModeEnabled != val) {
        mWrapModeEnabled = val;
        emit wrapModeEnabledChanged(mWrapModeEnabled);
    }
}
bool ScintillaSettings::isWrapModeEnabled()
{
    return mWrapModeEnabled;
}

void ScintillaSettings::setWrapMode(int val)
{
    if(mWrapMode != val) {
        mWrapMode = val;
    }
}
int ScintillaSettings::getWrapMode()
{
    return mWrapMode;
}


void ScintillaSettings::setIndentGuideEnabled(bool val)
{
    if(mIndentGuideEnabled != val) {
        mIndentGuideEnabled = val;
        emit indentGuideEnabledChanged(mIndentGuideEnabled);
    }
}
bool ScintillaSettings::isIndentGuideEnabled()
{
    return mIndentGuideEnabled;
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
