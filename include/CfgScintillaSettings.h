
#ifndef __CFG_SCINTILLA_SETTINGS_H_
 #define __CFG_SCINTILLA_SETTINGS_H_

#include <QObject>
#include <QString>
#include <QStringList>


class ScintillaSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool         showLineNumbersEnabled      READ isShowLineNumbersEnabled       WRITE setShowLineNumbersEnabled     )

    Q_PROPERTY(bool         eolVisible                  READ isEolVisible                   WRITE setEolVisible                 )
    Q_PROPERTY(bool         whiteSpaceVisible           READ isWhiteSpaceVisible            WRITE setWhiteSpaceVisible          )
    Q_PROPERTY(int          whiteSpaceVisibleMode       READ getWhiteSpaceVisibleMode       WRITE setWhiteSpaceVisibleMode      )
    Q_PROPERTY(bool         showWhiteCharsEnabled       READ isShowWhiteCharsEnabled        WRITE setShowWhiteCharsEnabled      )

    Q_PROPERTY(bool         wrapModeEnabled             READ isWrapModeEnabled              WRITE setWrapModeEnabled            )
    Q_PROPERTY(int          wrapMode                    READ getWrapMode                    WRITE setWrapMode                   )

    Q_PROPERTY(bool         indentGuideEnabled          READ isIndentGuideEnabled           WRITE setIndentGuideEnabled         )


    Q_PROPERTY(QStringList  codecAvailable              READ getCodecAvailable              WRITE setCodecAvailable             )



public:
    explicit ScintillaSettings();

    bool isShowLineNumbersEnabled();
    bool isEolVisible();
    bool isWhiteSpaceVisible();
    int getWhiteSpaceVisibleMode();
    bool isShowWhiteCharsEnabled();

    bool isWrapModeEnabled();
    int getWrapMode();

    bool isIndentGuideEnabled();

    const QStringList& getCodecAvailable();
    void addCodecAvailable(const QString &codec);
    void delCodecAvailable(const QString &codec);


signals:
    void showLineNumbersEnabledChanged(bool val);

    void eolVisibleChanged(bool val);
    void whiteSpaceVisibleChanged(bool val);
    void showWhiteCharsEnabledChanged(bool val);

    void wrapModeEnabledChanged(bool val);

    void indentGuideEnabledChanged(bool val);


public slots:
    void setShowLineNumbersEnabled(bool val);

    void setEolVisible(bool val);
    void setWhiteSpaceVisible(bool val);
    void setWhiteSpaceVisibleMode(int val);
    void setShowWhiteCharsEnabled(bool val);

    void setWrapModeEnabled(bool val);
    void setWrapMode(int val);

    void setIndentGuideEnabled(bool val);


    void setCodecAvailable(const QStringList &codecs);


private:
    bool mShowLineNumbersEnabled;

    bool mEolVisible;
    bool mEolVisiblePriv;
    bool mWhiteSpaceVisible;
    bool mWhiteSpaceVisiblePriv;
    int  mWhiteSpaceVisibleMode;
    bool mShowWhiteCharsEnabled;

    bool mWrapModeEnabled;
    int  mWrapMode;

    bool mIndentGuideEnabled;

    QStringList mCodecAvailable;


};

#endif //__CFG_SCINTILLA_SETTINGS_H_
