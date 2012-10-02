#ifndef __MANAGED_TOOLBAR_DIALOG_H_
 #define __MANAGED_TOOLBAR_DIALOG_H_

#include <QDialog>

namespace Ui {
class QtManagedToolBarDialog;
}

class QtManagedToolBarDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QtManagedToolBarDialog(QWidget *parent = 0);
    ~QtManagedToolBarDialog();
    
private:
    Ui::QtManagedToolBarDialog *ui;
};

#endif // __MANAGED_TOOLBAR_DIALOG_H_
