#include "qtpopup.h"
#include "ui_qtpopup.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QTimeLine>

static const int AlphaSolid       = 240;
static const int AlphaTransparent = 200;
static const int Height           = 80;
static const int StepCount        = 40;


QtPopup::QtPopup(const QString& header, const QString& message, Qt::Alignment align, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QtPopupp)
{
    ui->setupUi(this);

    align_ = align;

    if ( align & Qt::AlignTop ) {
        initialPos_ = -Height;
        direction_ = 1;
    }
    else {
        initialPos_ = parent->height();
        direction_ = -1;
    }
    setGeometry(0, initialPos_, 100, Height);
    hidden_ = true;
    curFrame_ = 0;

    timer_ = new QTimer();
    connect(timer_, SIGNAL(timeout()), SLOT(onTimer()));

    timeLine_ = new QTimeLine(300);
    timeLine_->setFrameRange(0, StepCount);
    connect(timeLine_, SIGNAL(frameChanged(int)), SLOT(makeStep(int)));

    setAlpha(AlphaTransparent);
}

QtPopup::~QtPopup()
{
    delete ui;
}

int QtPopup::bestWidth()
{
    QLabel *l = ui->lblMessage;
    return QFontMetrics(l->font()).boundingRect(l->text()).width() + 50;
}

void QtPopup::popup(int seconds) {
    timerTicks_ = seconds;
    ui->lblTimer->setText(QString::number(timerTicks_));
    timer_->start(1000);

    hidden_ = true;
    timeLine_->start();
    show();
}

void QtPopup::setAlpha(int alpha) {
    setStyleSheet(QString(styleSheet_).replace("ALPHA", QString::number(alpha)));

    static QString labelStyleSheet("QFrame {border: 0px; background-color: rgb(255, 255, 255, 0);}");
    ui->lblMessage->setStyleSheet(labelStyleSheet);
    ui->lblTimer->setStyleSheet(labelStyleSheet);
    ui->lblTitle->setStyleSheet(labelStyleSheet);
}

void QtPopup::enterEvent(QEvent* event) {
    setAlpha(AlphaSolid);
    QFrame::enterEvent(event);
}

void QtPopup::leaveEvent(QEvent* event) {
    setAlpha(AlphaTransparent);
    QFrame::leaveEvent(event);
}

void QtPopup::mousePressEvent(QMouseEvent*) {
    timer_->stop();
    dismiss();
}

void QtPopup::onTimer() {
    timerTicks_--;
    ui->lblTimer->setText(QString::number(timerTicks_));
    if ( timerTicks_ == 0 ) {
        timer_->stop();
        dismiss();
    }
}

void QtPopup::makeStep(int frame) {
    curFrame_ = frame;
    const int step = direction_ * Height / StepCount;
    if ( hidden_ ) {
        setGeometry(x(), initialPos_ + step * frame, width(), Height - 2);
    }
    else {
        setGeometry(x(), initialPos_ + step * (StepCount - frame), width(), Height - 2);
        if ( frame >= StepCount ) {
            emit closed();
            deleteLater();
        }
    }
}

void QtPopup::updatePosition() {
    int x, y;

    if ( align_ & Qt::AlignBottom ) {
        initialPos_ = parentWidget()->height();
    }

    // vertical pos
    const int step = direction_ * Height / StepCount;
    if ( hidden_ )
        y = initialPos_ + step * curFrame_;
    else {
        y = initialPos_ + step * (StepCount - curFrame_);
    }

    // horizontal pos
    int width = bestWidth();
    int pWidth = parentWidget()->width();
    if ( align_ & Qt::AlignLeft ) {
        x = 10;
    }
    else if ( align_ & Qt::AlignCenter ) {
        x = (pWidth - width) / 2;
    }
    else {
        x = (pWidth - width) - 10;
    }

    setGeometry( x, y, width, Height - 2);
}

void QtPopup::dismiss() {
    timeLine_->stop();
    hidden_ = false;
    timeLine_->start();
}
