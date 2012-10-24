#ifndef __PAGE_SCINTILLA_H_
 #define __PAGE_SCINTILLA_H_

#include "CfgAppSettings.h"

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
    explicit PageScintilla(CfgAppSettings *settings, QWidget *parent = 0);
    ~PageScintilla();
    
private:
    Ui::PageScintilla *ui;
};

}
}

#endif // __PAGE_SCINTILLA_H_
