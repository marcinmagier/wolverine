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

class QTimer;
class QTimeLine;

namespace Ui {
class QtPopup;
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

    Ui::QtPopup *ui;
};

#endif // __QT_POPUP_H_
