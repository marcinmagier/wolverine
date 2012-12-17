
#ifndef __PAGE_GENERAL_H_
 #define __PAGE_GENERAL_H_


class AppSettings;

#include <QWidget>


namespace Ui {
class PageGeneral;
}


namespace Wolverine {
namespace Settings {


class PageGeneral : public QWidget
{
    Q_OBJECT
    
public:
    explicit PageGeneral(AppSettings *settings, QWidget *parent = 0);
    ~PageGeneral();
    
private slots:
    void on_cmbLanguage_currentIndexChanged(int index);
    void on_btnLogFilePathDlg_clicked();


private:
    QStringList mTranslations;
    Ui::PageGeneral *ui;
};


}
}

#endif // __PAGE_GENERAL_H_
