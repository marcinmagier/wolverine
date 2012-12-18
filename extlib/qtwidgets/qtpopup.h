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
 *  @file       qtpopup.h
 *  @brief      QtPopup class interface.
 */


#ifndef __QT_POPUP_H_
 #define __QT_POPUP_H_


#include <QFrame>
#include <QList>
#include <QPoint>


#define POPUP_MARGIN    10


class QTimer;
class QTimeLine;

namespace Ui {
class IQtPopup;
}

class QtPopup;



class QtPopupBase : public QFrame
{
    Q_OBJECT

protected:
    enum PopupState {
        InitState,
        OpeningState,
        TimerState,
        ClosingState
    };

    enum PopupAlpha {
        AlphaSolid = 245,
        AlphaTransparent = 100
    };

    static const int ANIMATION_FRAME_COUNT;

public:
    QtPopupBase(const QString &title, const QString &message);
    virtual ~QtPopupBase();

signals:
    void action();
    void closed();

protected slots:
    void onTimerSec();
    void onAnimationStep(int frame);


protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual QSize getSize() const;
    virtual void makeInitStep() = 0;
    virtual void makeOpeningStep(int frame) = 0;
    virtual void makeClosingStep(int frame) = 0;

    void popup(int timeout);

    void setInitialPos(int pos);
    void changeInitialPos(int move);
    void setAlpha(int alpha);
    QSize calculateSize();
    void dismiss();
    static void updateTheme(const QColor &fg, const QColor &bg);


    int mPosition;
    int mTimerSecTicks;
    int mCurrentAlpha;
    PopupState mState;
    QTimer *mTimerSec;
    QTimeLine *mTimeLineAnimation;

    static QString sStyleSheetFrame;
    static QString sStyleSheetLabel;

    Ui::IQtPopup *ui;

    friend class QtPopup;
};



class QtPopupFlash : public QtPopupBase
{
    Q_OBJECT

public:
    explicit QtPopupFlash(const QString &title, const QString &message);
    virtual ~QtPopupFlash();

protected:
    virtual void makeInitStep();
    virtual void makeOpeningStep(int frame);
    virtual void makeClosingStep(int frame);
};



class QtPopupMove : public QtPopupBase
{
    Q_OBJECT

public:
    explicit QtPopupMove(const QString &title, const QString &message);
    virtual ~QtPopupMove();

protected:
    virtual void makeInitStep();
    virtual void makeOpeningStep(int frame);
    virtual void makeClosingStep(int frame);

private:
    QPoint mFinalPos;
    QPoint mInitPos;
};



class QtPopupRise : public QtPopupBase
{
    Q_OBJECT

public:
    explicit QtPopupRise(const QString &title, const QString &message);
    virtual ~QtPopupRise();

protected:
    virtual QSize getSize() const;
    virtual void makeInitStep();
    virtual void makeOpeningStep(int frame);
    virtual void makeClosingStep(int frame);

private:
    QSize mFinalSize;
    QPoint mFinalPos;
    QPoint mInitPos;
};






class QtPopup : public QObject
{
    Q_OBJECT
    
protected:
    QtPopup();


public:
    ~QtPopup();

    static bool popup( QtPopupBase *popupInstance, QWidget *parent=0);
    static void setTheme(const QColor &foreground, const QColor &background);
    static void setTimeout(int seconds);
    static void deleteInstance();

private slots:
    void onPopupClose();


private:

    int mPosition;
    static int sTimeout;
    static QtPopup *sInstance;
    QList<QtPopupBase*> mPopups;

};

#endif // __QT_POPUP_H_
