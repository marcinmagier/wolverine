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
 *  @file       qtpopup_i.cpp
 *  @brief      IQtPopup class implementation.
 */


#include "qtpopup.h"
#include "ui_qtpopup.h"


#include <QTimer>
#include <QTimeLine>
#include <QMouseEvent>




#define FRAME_STYLE_PATTERN     "QFrame {"                                  \
                                "border: 1px solid; "                       \
                                "border-color: rgb(%1, %2, %3, ALPHA);"     \
                                "border-radius: 10px; "                     \
                                "background-color: rgb(%4, %5, %6, ALPHA);" \
                                "}"

#define LABEL_STYLE_PATTERN     "QLabel {"                                  \
                                "border: 0px;"                              \
                                "color: rgb(%1, %2, %3, ALPHA);"            \
                                "background-color: rgb(255, 255, 255, 0);"  \
                                "}"



QString IQtPopup::sStyleSheetFrame;
QString IQtPopup::sStyleSheetLabel;
const int IQtPopup::ANIMATION_FRAME_COUNT = 40;




/**
 *  Constructor.
 *
 * @param title
 * @param message
 */
IQtPopup::IQtPopup(const QString &title, const QString &message) :
    ui(new Ui::IQtPopup)
{
    hide();
    ui->setupUi(this);
    ui->lblTitle->setText(QString("<b>%1</b>").arg(title));
    ui->lblMessage->setText(message);

    mState = IQtPopup::InitState;

    mTimerSec = new QTimer();
    connect( mTimerSec, SIGNAL(timeout()),
                  this, SLOT(onTimerSec()) );

    mTimeLineAnimation = new QTimeLine();
    mTimeLineAnimation->setFrameRange(0, ANIMATION_FRAME_COUNT);
    connect( mTimeLineAnimation, SIGNAL(frameChanged(int)),
                           this, SLOT(onAnimationStep(int)) );
}


/**
 *  Destructor.
 */
IQtPopup::~IQtPopup()
{
    delete ui;
}


/**
 *  Enter event handler.
 *
 * @param event
 */
//virtual
void IQtPopup::enterEvent(QEvent *event)
{
    if(mState != IQtPopup::TimerState)
        return;

    setAlpha(IQtPopup::AlphaSolid);
    QFrame::enterEvent(event);
}


/**
 *  Leave event handler.
 *
 * @param event
 */
//virtual
void IQtPopup::leaveEvent(QEvent *event)
{
    if(mState != IQtPopup::TimerState)
        return;

    setAlpha(IQtPopup::AlphaTransparent);
    QFrame::leaveEvent(event);
}


/**
 *  Mouse press event handler.
 *
 * @param event
 */
//virtual
void IQtPopup::mousePressEvent(QMouseEvent *event)
{
    if(mState != IQtPopup::TimerState)
        return;

    if(event->button() & Qt::LeftButton) {
        dismiss();
    }

    emit action();
}


/**
 * Shows popup frame
 *
 * @param timeout
 */
void IQtPopup::popup(int timeout)
{
    mTimerSecTicks = timeout;
    ui->lblTimer->setText(QString::number(mTimerSecTicks));
    makeInitStep();

    mTimeLineAnimation->setDirection(QTimeLine::Forward);
    mTimeLineAnimation->start();

    mState = IQtPopup::OpeningState;
    show();
}


/**
 * Sets position (height) where popup is placed.
 *
 * @param pos
 */
void IQtPopup::setInitialPos(int pos)
{
    mPosition = pos;

}


/**
 * Sets alpha
 *
 * @param alpha
 */
void IQtPopup::setAlpha(int alpha)
{
    QString style = QString(sStyleSheetFrame).replace("ALPHA", QString::number(alpha));
    setStyleSheet(style);

    style = QString(sStyleSheetLabel).replace("ALPHA", QString::number(alpha));
    ui->lblMessage->setStyleSheet(style);
    ui->lblTimer->setStyleSheet(style);
    ui->lblTitle->setStyleSheet(style);

}


/**
 *  Calculates preferred width of popup.
 *
 * @return
 */
int IQtPopup::calculateWidth()
{
    QLabel *lbl = ui->lblMessage;
    return QFontMetrics(lbl->font()).boundingRect(lbl->text()).width() + 30;
}

/**
 *  Updates popup's colors.
 *
 * @param fg
 * @param bg
 */
//static
void IQtPopup::updateTheme(const QColor &fg, const QColor &bg)
{
    sStyleSheetFrame = QString(FRAME_STYLE_PATTERN).arg(fg.red()).arg(fg.green()).arg(fg.blue())
                                                   .arg(bg.red()).arg(bg.green()).arg(bg.blue());

    sStyleSheetLabel = QString(LABEL_STYLE_PATTERN).arg(fg.red()).arg(fg.green()).arg(fg.blue());
}


/**
 *  On timer (seconds) slot.
 */
//slot
void IQtPopup::onTimerSec()
{
    if(mState != IQtPopup::TimerState)
        return;

    mTimerSecTicks--;
    ui->lblTimer->setText(QString::number(mTimerSecTicks));

    if(mTimerSecTicks == 0)
        dismiss();
}


/**
 *  On animation step slot.
 *
 * @param frame
 */
//slot
void IQtPopup::onAnimationStep(int frame)
{
    if(mState == IQtPopup::OpeningState) {
        makeOpeningStep(frame);
        if(frame >= ANIMATION_FRAME_COUNT) {
            mTimeLineAnimation->stop();
            mTimerSec->start(1000);
            mState = IQtPopup::TimerState;
        }
    }
    else if(mState == IQtPopup::ClosingState) {
        makeClosingStep(frame);
        if(frame <= 0) {
            mTimeLineAnimation->stop();
            emit closed();
            deleteLater();
        }
    }
}


/**
 *  Closes popup.
 */
void IQtPopup::dismiss()
{
    mTimerSec->stop();
    mState = IQtPopup::ClosingState;
    mTimeLineAnimation->setDirection(QTimeLine::Backward);
    mTimeLineAnimation->start();
}


