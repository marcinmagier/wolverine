#include "qtpopupo.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QTimeLine>

static const int AlphaSolid       = 240;
static const int AlphaTransparent = 200;
static const int Height           = 80;
static const int StepCount        = 40;


QtPopupOld::QtPopupOld(const QString& header, const QString& message, Qt::Alignment align, QWidget *parent) :
    QFrame(parent)
{

    align_ = align;

    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Raised);
    setMaximumWidth(600);

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

    headerL_ = new QLabel(QString("<b>%1</b>").arg(header));
    headerL_->setMaximumHeight(20);
    messageL_ = new QLabel(message);
    messageL_->setAlignment(Qt::AlignCenter);
    messageL_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    messageL_->setWordWrap(true);

    timerL_ = new QLabel("");
    timerL_->setMaximumWidth(30);
    timerL_->setAlignment(Qt::AlignCenter);
    timerL_->setMaximumHeight(20);

    QVBoxLayout* vBox = new QVBoxLayout();
    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->setContentsMargins(0, 2, 0, 2);
    vBox->setContentsMargins(10, 2, 10, 2);
    vBox->setSpacing(0);

    hBox->addWidget(headerL_);
    hBox->addWidget(timerL_);

    vBox->addLayout(hBox);
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    vBox->addWidget(line);
    vBox->addWidget(messageL_);
    setLayout(vBox);

    timer_ = new QTimer();
    connect(timer_, SIGNAL(timeout()), SLOT(onTimer()));

    timeLine_ = new QTimeLine(300);
    timeLine_->setFrameRange(0, StepCount);
    connect(timeLine_, SIGNAL(frameChanged(int)), SLOT(makeStep(int)));

    QColor bgColor = palette().color(QPalette::ToolTipBase);
    QColor fgColor = palette().color(QPalette::ToolTipText);
    styleSheet_ = QString("QFrame {border: 1px solid gray; border-radius: 4px; background-color: rgb(%1, %2, %3, ALPHA);} QLabel { color: rgb(%4, %5, %6); }")
        .arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue())
        .arg(fgColor.red()).arg(fgColor.green()).arg(fgColor.blue());

    setAlpha(AlphaTransparent);
}

int QtPopupOld::bestWidth()
{
    return QFontMetrics(messageL_->font()).boundingRect(messageL_->text()).width() + 50;
}

void QtPopupOld::popup(int seconds) {
    timerTicks_ = seconds;
    timerL_->setText(QString::number(timerTicks_));
    timer_->start(1000);

    hidden_ = true;
    timeLine_->start();
    show();
}

void QtPopupOld::setAlpha(int alpha) {
    setStyleSheet(QString(styleSheet_).replace("ALPHA", QString::number(alpha)));

    static QString labelStyleSheet("QFrame {border: 0px; background-color: rgb(255, 255, 255, 0);}");
    messageL_->setStyleSheet(labelStyleSheet);
    timerL_->setStyleSheet(labelStyleSheet);
    headerL_->setStyleSheet(labelStyleSheet);
}

void QtPopupOld::enterEvent(QEvent* event) {
    setAlpha(AlphaSolid);
    QFrame::enterEvent(event);
}

void QtPopupOld::leaveEvent(QEvent* event) {
    setAlpha(AlphaTransparent);
    QFrame::leaveEvent(event);
}

void QtPopupOld::mousePressEvent(QMouseEvent*) {
    timer_->stop();
    dismiss();
}

void QtPopupOld::onTimer() {
    timerTicks_--;
    timerL_->setText(QString::number(timerTicks_));
    if ( timerTicks_ == 0 ) {
        timer_->stop();
        dismiss();
    }
}

void QtPopupOld::makeStep(int frame) {
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

void QtPopupOld::updatePosition() {
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

void QtPopupOld::dismiss() {
    timeLine_->stop();
    hidden_ = false;
    timeLine_->start();
}


