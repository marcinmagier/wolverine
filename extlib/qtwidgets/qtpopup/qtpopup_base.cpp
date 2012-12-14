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
 *  @file       qtpopup_base.cpp
 *  @brief      QtPopupBase class implementation.
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



QString QtPopupBase::sStyleSheetFrame;
QString QtPopupBase::sStyleSheetLabel;
const int QtPopupBase::ANIMATION_FRAME_COUNT = 40;




/**
 *  Constructor.
 *
 * @param title
 * @param message
 */
QtPopupBase::QtPopupBase(const QString &title, const QString &message) :
    ui(new Ui::IQtPopup)
{
    hide();
    ui->setupUi(this);
    ui->lblTitle->setText(QString("<b>%1</b>").arg(title));
    ui->lblMessage->setText(message);

    mState = QtPopupBase::InitState;

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
QtPopupBase::~QtPopupBase()
{
    delete ui;
}


/**
 *  Enter event handler.
 *
 * @param event
 */
//virtual
void QtPopupBase::enterEvent(QEvent *event)
{
    if(mState != QtPopupBase::TimerState)
        return;

    setAlpha(QtPopupBase::AlphaSolid);
    QFrame::enterEvent(event);
}


/**
 *  Leave event handler.
 *
 * @param event
 */
//virtual
void QtPopupBase::leaveEvent(QEvent *event)
{
    if(mState != QtPopupBase::TimerState)
        return;

    setAlpha(QtPopupBase::AlphaTransparent);
    QFrame::leaveEvent(event);
}


/**
 *  Mouse press event handler.
 *
 * @param event
 */
//virtual
void QtPopupBase::mousePressEvent(QMouseEvent *event)
{
    if(mState != QtPopupBase::TimerState)
        return;

    if(event->button() & Qt::LeftButton) {
        dismiss();
    }

    emit action();
}


/**
 *  Shows popup frame
 *
 * @param timeout
 */
void QtPopupBase::popup(int timeout)
{
    mTimerSecTicks = timeout;
    ui->lblTimer->setText(QString::number(mTimerSecTicks));
    makeInitStep();

    mTimeLineAnimation->setDirection(QTimeLine::Forward);
    mTimeLineAnimation->start();

    mState = QtPopupBase::OpeningState;
    show();
}


/**
 *  Sets position (height) where popup is placed.
 *
 * @param pos
 */
void QtPopupBase::setInitialPos(int pos)
{
    mPosition = pos;

}


/**
 *  Changes position (height) where popup is palced.
 *
 * This function is used when popup should be moved up after another popup was closed.
 *
 * @param move
 */
void QtPopupBase::changeInitialPos(int move)
{
    mPosition = mPosition - move;
    this->move(this->geometry().x(), this->geometry().y()-move);
}


/**
 *  Sets alpha
 *
 * @param alpha
 */
void QtPopupBase::setAlpha(int alpha)
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
QSize QtPopupBase::calculateSize()
{
    #define LBL_PADDING 30
    QLabel *lbl = ui->lblMessage;
    int width = QFontMetrics(lbl->font()).boundingRect(lbl->text()).width() + LBL_PADDING;
    return QSize(width, this->size().height());
}

/**
 *  Updates popup's colors.
 *
 * @param fg
 * @param bg
 */
//static
void QtPopupBase::updateTheme(const QColor &fg, const QColor &bg)
{
    sStyleSheetFrame = QString(FRAME_STYLE_PATTERN).arg(fg.red()).arg(fg.green()).arg(fg.blue())
                                                   .arg(bg.red()).arg(bg.green()).arg(bg.blue());

    sStyleSheetLabel = QString(LABEL_STYLE_PATTERN).arg(fg.red()).arg(fg.green()).arg(fg.blue());
}


/**
 *  On timer (seconds) slot.
 */
//slot
void QtPopupBase::onTimerSec()
{
    if(mState != QtPopupBase::TimerState)
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
void QtPopupBase::onAnimationStep(int frame)
{
    if(mState == QtPopupBase::OpeningState) {
        makeOpeningStep(frame);
        if(frame >= ANIMATION_FRAME_COUNT) {
            mTimeLineAnimation->stop();
            mTimerSec->start(1000);
            mState = QtPopupBase::TimerState;
        }
    }
    else if(mState == QtPopupBase::ClosingState) {
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
void QtPopupBase::dismiss()
{
    mTimerSec->stop();
    mState = QtPopupBase::ClosingState;
    mTimeLineAnimation->setDirection(QTimeLine::Backward);
    mTimeLineAnimation->start();
}


