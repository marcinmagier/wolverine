/**************************************************************************************************
**
**  Copyright (C) 2012-2013 Magier Marcin
**
**  This program is free software: you can redistribute it and/or modify it under the terms
**  of the GNU General Public License as published by the Free Software Foundation,
**  either version 3 of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
**  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**  See the GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************************************/

/**
 *  @file       qtpopup.cpp
 *  @brief      QtPopup class implementation.
 */


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
    ui(new Ui::QtPopup)
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

    QColor bgColor = palette().color(QPalette::ToolTipBase);
    QColor fgColor = palette().color(QPalette::ToolTipText);
    styleSheet_ = QString("QFrame {"
                          "border: 1px solid; "
                          "border-color: rgb(0, 0, 0, ALPHA);"
                          "border-radius: 4px; "
                          "background-color: rgb(%1, %2, %3, ALPHA);"
                          "}"
                          "QLabel {"
                          "color: rgb(%4, %5, %6, ALPHA);"
                          "}")
        .arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue())
        .arg(fgColor.red()).arg(fgColor.green()).arg(fgColor.blue());

    setAlpha(100);
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
        //setAlpha(255/StepCount * step);
    }
    else {
        //setGeometry(x(), initialPos_ + step * (StepCount - frame), width(), Height - 2);
        setAlpha(255/StepCount * (StepCount-frame));
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
