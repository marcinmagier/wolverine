#ifndef QTDIALOGSETTINGS_H
#define QTDIALOGSETTINGS_H

#include <QDialog>

namespace Ui {
class QtDialogSettings;
}

class QtDialogSettings : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtDialogSettings(QWidget *parent = 0);
    ~QtDialogSettings();
    
private:
    Ui::QtDialogSettings *ui;
};

#endif // QTDIALOGSETTINGS_H
