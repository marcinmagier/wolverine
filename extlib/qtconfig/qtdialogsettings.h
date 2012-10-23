#ifndef __QT_DIALOG_SETTINGS_H_
  #define __QT_DIALOG_SETTINGS_H_

#include "qtconfig.h"
#include <QDialog>

class QtSettingsPage;

namespace Ui {
class QtDialogSettings;
}


class QtDialogSettings : public QDialog
{
    Q_OBJECT

    
public:
    explicit QtDialogSettings(QtConfig *config, QWidget *parent = 0);
    ~QtDialogSettings();

    void addSettingsPage(const QString &name, QWidget *page);
    void addSettingsPage(const QString &name, const QString &parent, QWidget *page);
    void addPluginSettingsPage(const QString &name, QWidget *page);


private:
    Ui::QtDialogSettings *ui;
    QtConfig *m_config;
};

#endif // __QT_DIALOG_SETTINGS_H_
