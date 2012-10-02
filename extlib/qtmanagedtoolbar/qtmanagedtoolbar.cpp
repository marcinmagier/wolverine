
#include "qtmanagedtoolbar.h"
#include "qtmanagedtoolbardialog.h"

#include <QMenu>
#include <QContextMenuEvent>


QtManagedToolBar::QtManagedToolBar(QWidget *parent) :
    QToolBar(parent)
{
    m_isManagerEnabled = true;
}


void QtManagedToolBar::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *action = menu.addAction(tr("Test"));

    if(m_isManagerEnabled) {
        action = menu.addAction(tr("Customize"));
        action->setIcon(QIcon(":/settings.png"));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
    }
    menu.exec(event->globalPos());
}


void QtManagedToolBar::showManagerDialog()
{
    QtManagedToolBarDialog dlg(this);
    if(dlg.exec()) {

    }
}



void QtManagedToolBar::addAction(QAction *action)
{
    QToolBar::addAction(action);
    m_actionsAvailable.append(action);
    m_actionsVisible.append(action);
}

void QtManagedToolBar::addActions(QList<QAction*> actions)
{
    QToolBar::addActions(actions);
    m_actionsAvailable.append(actions);
    m_actionsVisible.append(actions);
}

void QtManagedToolBar::insertAction(QAction *before, QAction *action)
{
    QToolBar::insertAction(before, action);
    //TODO
}

void QtManagedToolBar::insertActions(QAction *before, QList<QAction*> actions)
{
    QToolBar::insertActions(before, actions);
    //TODO
}

void QtManagedToolBar::removeAction(QAction *action)
{
    QToolBar::removeAction(action);
    m_actionsAvailable.removeOne(action);
    m_actionsVisible.removeOne(action);
}

//QToolBar
QAction *QtManagedToolBar::addAction(const QString &text)
{
    QAction *action = QToolBar::addAction(text);
    m_actionsAvailable.append(action);
    m_actionsVisible.append(action);
    return action;
}

QAction *QtManagedToolBar::addAction(const QIcon &icon, const QString &text)
{
    QAction *action = QToolBar::addAction(icon, text);
    m_actionsAvailable.append(action);
    m_actionsVisible.append(action);
    return action;
}

QAction *QtManagedToolBar::addAction(const QString &text, const QObject *receiver, const char* member)
{
    QAction *action = QToolBar::addAction(text, receiver, member);
    m_actionsAvailable.append(action);
    m_actionsVisible.append(action);
    return action;
}

QAction *QtManagedToolBar::addAction(const QIcon &icon, const QString &text, const QObject *receiver, const char* member)
{
    QAction *action = QToolBar::addAction(icon, text, receiver, member);
    m_actionsAvailable.append(action);
    m_actionsVisible.append(action);
    return action;
}
