#ifndef QTPOPUP_H
#define QTPOPUP_H

#include <QFrame>

class QLabel;
class QTimer;
class QTimeLine;


class QtPopup : public QFrame
{
    Q_OBJECT
public:
    explicit QtPopup(const QString&, const QString&, Qt::Alignment, QWidget *parent);
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

    QLabel* headerL_;
    QLabel* messageL_;
    QLabel* timerL_;
    int timerTicks_;
    QTimer* timer_;
    QTimeLine* timeLine_;
    bool hidden_;
    QString styleSheet_;
    Qt::Alignment align_;

    int initialPos_;
    int direction_;
    int curFrame_;
};

#endif // QTPOPUP_H
