
#ifndef __PAGE_SCINTILLA_H_
 #define __PAGE_SCINTILLA_H_


class AppSettings;

#include <QWidget>


namespace Ui {
class PageScintilla;
}


namespace Wolverine {
namespace Settings {


class PageScintilla : public QWidget
{
    Q_OBJECT
    
public:
    explicit PageScintilla(AppSettings *settings, QWidget *parent = 0);
    ~PageScintilla();
    
private:
    Ui::PageScintilla *ui;
};

}
}

#endif // __PAGE_SCINTILLA_H_
