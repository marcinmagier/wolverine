
#ifndef __PAGE_EDITOR_H_
 #define __PAGE_EDITOR_H_


class AppSettings;

#include <QWidget>


namespace Ui {
class PageEditor;
}


namespace Wolverine {
namespace Settings {


class PageEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit PageEditor(AppSettings *settings, QWidget *parent = 0);
    ~PageEditor();
    
private:
    Ui::PageEditor *ui;
};

}
}

#endif // __PAGE_EDITOR_H_
