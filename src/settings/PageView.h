
#ifndef __PAGE_VIEW_H_
 #define __PAGE_VIEW_H_


class AppSettings;

#include <QWidget>


namespace Ui {
class PageView;
}


namespace Wolverine {
namespace Settings {


class PageView : public QWidget
{
    Q_OBJECT
    
public:
    explicit PageView(AppSettings *settings, QWidget *parent = 0);
    ~PageView();
    
private:
    Ui::PageView *ui;
};

}
}

#endif // __PAGE_VIEW_H_
