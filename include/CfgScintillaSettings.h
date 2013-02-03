
#ifndef __CFG_SCINTILLA_SETTINGS_H_
 #define __CFG_SCINTILLA_SETTINGS_H_

#include <QObject>
#include <QString>
#include <QStringList>


class ScintillaSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool         showLineNumbersEnabled      READ isShowLineNumbersEnabled       WRITE setShowLineNumbersEnabled     )


    Q_PROPERTY(QStringList  codecAvailable              READ getCodecAvailable              WRITE setCodecAvailable             )



public:
    explicit ScintillaSettings();

    bool isShowLineNumbersEnabled();

    const QStringList& getCodecAvailable();
    void addCodecAvailable(const QString &codec);
    void delCodecAvailable(const QString &codec);


signals:
    void showLineNumbersEnabledChanged(bool val);


public slots:
    void setShowLineNumbersEnabled(bool val);

    void setCodecAvailable(const QStringList &codecs);


private:
    bool mShowLineNumbersEnabled;
    QStringList mCodecAvailable;


};

#endif //__CFG_SCINTILLA_SETTINGS_H_
