
#ifndef __CFG_SCINTILLA_SETTINGS_H_
 #define __CFG_SCINTILLA_SETTINGS_H_

#include <QObject>
#include <QString>

class ScintillaSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool     showLineNumbersEnabled      READ isShowLineNumbersEnabled       WRITE setShowLineNumbersEnabled     )



public:
    explicit ScintillaSettings();

    bool isShowLineNumbersEnabled();


signals:
    void showLineNumbersEnabledChanged(bool val);


public slots:
    void setShowLineNumbersEnabled(bool val);


private:
    bool mShowLineNumbersEnabled;


};

#endif //__CFG_SCINTILLA_SETTINGS_H_
