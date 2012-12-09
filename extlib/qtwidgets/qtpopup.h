
#ifndef __QT_POPUP_H_
 #define __QT_POPUP_H_

#include <QFrame>

class QTimer;
class QTimeLine;

namespace Ui {
class QtPopupp;
}

class QtPopup : public QFrame
{
    Q_OBJECT
    
public:
    explicit QtPopup(const QString&, const QString&, Qt::Alignment, QWidget *parent = 0);
    ~QtPopup();

    void popup(int seconds = 10);
    void dismiss();
    Qt::Alignment align() const { return align_; }
    void updatePosition();
    
signals:
    void closed();

public slots:
    void onTimer();
    void makeStep(int);

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent *);

private:
    int bestWidth();
    void setAlpha(int alpha);


    int timerTicks_;
    QTimer* timer_;
    QTimeLine* timeLine_;
    bool hidden_;
    QString styleSheet_;
    Qt::Alignment align_;

    int initialPos_;
    int direction_;
    int curFrame_;

    Ui::QtPopupp *ui;
};

#endif // __QT_POPUP_H_
