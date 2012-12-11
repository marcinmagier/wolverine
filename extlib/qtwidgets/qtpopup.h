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
#include <QLinkedList>

class QTimer;
class QTimeLine;

namespace Ui {
class IQtPopup;
}




class IQtPopup : public QFrame
{
    Q_OBJECT

public:
    IQtPopup(const QString &title, const QString &message);
    virtual ~IQtPopup();

signals:
    void action();
    void closed();

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    Ui::IQtPopup *ui;
};



class QtPopupMove : public IQtPopup
{
    Q_OBJECT

public:
    explicit QtPopupMove(const QString &title, const QString &message);
    virtual ~QtPopupMove();


};


class QtPopupFlash : public IQtPopup
{
    Q_OBJECT

public:
    explicit QtPopupFlash(const QString &title, const QString &message);
    virtual ~QtPopupFlash();
};




class QtPopup : public QObject
{
    Q_OBJECT
    
private:
    QtPopup();


public:
    ~QtPopup();

    static bool popup( IQtPopup *instance, QWidget *parent=0);
    static bool setTheme(const QColor &foreground, const QColor &background);
    static bool setTimeout(int seconds);
    static void deleteInstance();

private slots:
    void onPopupClose();


private:

    int mPosition;
    int mTimeout;

    QColor mColorFg;
    QColor mColorBg;

    static QtPopup *sInstance;
    QLinkedList<IQtPopup*> mPopups;

};

#endif // __QT_POPUP_H_
