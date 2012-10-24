#ifndef __QT_DIALOG_SETTINGS_H_
  #define __QT_DIALOG_SETTINGS_H_

#include "qtconfig.h"
#include <QDialog>

class QtSettingsPage;
class QCloseEvent;


namespace Ui {
class QtDialogSettings;
}


// REMARK
// Dialog title and icon is application specific. It should be set by successor class


class QtDialogSettings : public QDialog
{
    Q_OBJECT

    
public:
    explicit QtDialogSettings ( QtConfig *config, QWidget *parent = 0 );
    ~QtDialogSettings();

    void closeEvent ( QCloseEvent *e );

    void addSettingsPage( const QString &name, QWidget *page );
    void addSettingsPage( const QString &name, const QString &parent, QWidget *page );


signals:
    void applied();


public slots:
    void ok();
    virtual void accept();
    virtual void reject();
    int exec();

private:
    Ui::QtDialogSettings *ui;
    QtConfig *m_config;
};

#endif // __QT_DIALOG_SETTINGS_H_
