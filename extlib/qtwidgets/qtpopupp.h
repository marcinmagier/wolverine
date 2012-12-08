
#ifndef __QT_POPUP_H_
 #define __QT_POPUP_H_

#include <QFrame>

namespace Ui {
class QtPopupp;
}

class QtPopupp : public QFrame
{
    Q_OBJECT
    
public:
    explicit QtPopupp(QWidget *parent = 0);
    ~QtPopupp();
    
private:
    Ui::QtPopupp *ui;
};

#endif // __QT_POPUP_H_
