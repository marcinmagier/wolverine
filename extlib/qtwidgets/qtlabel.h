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
 *  @file       qtlabel.h
 *  @brief      QtLabel class interface.
 */



#ifndef __QT_LABEL_H_
 #define __QT_LABEL_H_


#include <QLabel>

class QTimer;
class QMouseEvent;

class QtLabel : public QLabel
{
    Q_OBJECT

public:
    explicit QtLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    explicit QtLabel(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0);

    void setLongClickTimeout(int timeout);
    int getLongClickTimeout();

signals:
    void clicked(Qt::MouseButton button);
    void clickedLong(Qt::MouseButton button);
    void doubleClicked(Qt::MouseButton button);



protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private slots:
    void onTimeout();

private:
    void initialize();

    QTimer *mTimer;
    int mTimerTimeout;
    Qt::MouseButton mMouseButton;

};

#endif // __QT_LABEL_H_
