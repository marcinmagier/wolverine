
#include "qtmanagedtoolbar.h"
#include "qtmanagedtoolbardialog.h"

#include <QApplication>
#include <QSettings>
#include <QMenu>
#include <QContextMenuEvent>


#define QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE	":/qtmanagedtoolbar/customize.png"


static int defToolbarCount = 0;
static const QString defToolbarName = "NoNamedToolbar";

static int defItemCount = 0;
static const QString defItemName = "NoNamedItem";


QtManagedToolBar::QtManagedToolBar(QWidget *parent) :
    QToolBar(parent)
{
    //This constructor should not be used in reliable application
    //Calculate unique name to prevent future problems
    QString toolbarName = defToolbarName + QString::number(defToolbarCount++);
    init(toolbarName);
}

QtManagedToolBar::QtManagedToolBar(QWidget *parent, const QString &toolbarName) :
    QToolBar(parent)
{ 
    init(toolbarName);
}

void QtManagedToolBar::init(const QString &name)
{
    m_toolbarName = name;
    m_actionsAvailable.clear();
    m_isManagerEnabled = true;
}




void QtManagedToolBar::addAction(QAction *action)
{
    addActionAvailable(action);
    QToolBar::addAction(action);
}

QAction* QtManagedToolBar::addAction(const QString &text)
{
    QAction *tmp = QToolBar::addAction(text);
    addActionAvailable(tmp);
    return tmp;
}

QAction* QtManagedToolBar::addAction(const QIcon &icon, const QString &text)
{
    QAction *tmp = QToolBar::addAction(icon, text);
    addActionAvailable(tmp);
    return tmp;
}

QAction* QtManagedToolBar::addAction(const QString &text, const QObject *receiver, const char* member)
{
    QAction *tmp = QToolBar::addAction(text, receiver, member);
    addActionAvailable(tmp);
    return tmp;
}

QAction* QtManagedToolBar::addAction(const QIcon &icon, const QString &text, const QObject *receiver, const char* member)
{
    QAction *tmp = QToolBar::addAction(icon, text, receiver, member);
    addActionAvailable(tmp);
    return tmp;
}


QAction* QtManagedToolBar::addWidget(QWidget *widget)
{
    QAction *tmp = QToolBar::addWidget(widget);
    addActionAvailable(tmp);
    return tmp;
}

QAction* QtManagedToolBar::insertWidget(QAction *before, QWidget *widget)
{
    QAction *tmp = QToolBar::insertWidget(before, widget);
    addActionAvailable(tmp);
    return tmp;
}


void QtManagedToolBar::addActions(QList<QAction*> actions)
{
    addActionsAvailable(actions);
    QWidget::addActions(actions);
}

void QtManagedToolBar::insertAction(QAction *before, QAction *action)
{
    addActionAvailable(action);
    QWidget::insertAction(before, action);
}

void QtManagedToolBar::insertActions(QAction *before, QList<QAction*> actions)
{
    addActionsAvailable(actions);
    QWidget::insertActions(before, actions);
}

void QtManagedToolBar::removeAction(QAction *action)
{
    m_actionsAvailable.removeAll(action);
    QWidget::removeAction(action);
}





void QtManagedToolBar::contextMenuEvent(QContextMenuEvent *event)
{
    if(m_isManagerEnabled) {
        QMenu *contextMenu = new QMenu(this);
        QAction *action = contextMenu->addAction(tr("Customize"));
        action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));

        contextMenu->exec(event->globalPos());

        delete contextMenu;
    }
}

void QtManagedToolBar::showContextMenu(QContextMenuEvent *event, QMenu *menu)
{
	if(m_isManagerEnabled) {
		QAction *action = menu->addAction(tr("Customize"));
		action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
		connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
	}

	menu->exec(event->globalPos());
}



void QtManagedToolBar::showManagerDialog()
{
    QtManagedToolBarDialog dlg(this);
    dlg.actionsAvailable = &m_actionsAvailable;
    QStringList tmpActionsVisible = createConfiguration();
    dlg.actionsVisible = &tmpActionsVisible;

    if(dlg.exec()) {
        applyConfiguration(tmpActionsVisible);
        saveConfig(tmpActionsVisible);
    }
}



void QtManagedToolBar::saveConfig()
{
    QStringList actionsVisible = createConfiguration();
    saveConfig(actionsVisible);
}

void QtManagedToolBar::saveConfig(const QStringList &actionList)
{
    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");

    if (!qset.isWritable())
        return;

    qset.setValue(m_toolbarName, QVariant::fromValue(actionList));
}

void QtManagedToolBar::restoreConfig()
{

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");
    QVariant var = qset.value(m_toolbarName);
    QStringList list = var.toStringList();

    applyConfiguration(list);
}




void QtManagedToolBar::addActionAvailable(QAction *action)
{
    if(action->text().isEmpty())
        action->setText( defItemName + QString::number(defItemCount++) );
    m_actionsAvailable.append(action);
}

void QtManagedToolBar::addActionsAvailable(QList<QAction *> actions)
{
    foreach(QAction *action, actions) {
        addActionAvailable(action);
    }
}




QAction* QtManagedToolBar::getActionAvailable(const QString &name)
{
    foreach(QAction *action, m_actionsAvailable) {
        if(action->text() == name)
            return action;
    }

    return 0;
}

void QtManagedToolBar::applyConfiguration(const QStringList &config)
{
    if(config.size() == 0)
        return;

    clear();
    foreach(QString item, config) {
        if(item == "Separator") {
            QToolBar::addSeparator();
            continue;
        }
        QAction *action = getActionAvailable(item);
        if(action)
             //Don't add action to m_actionsAvailable
            QToolBar::addAction(action);
    }
}

QStringList QtManagedToolBar::createConfiguration()
{
    QStringList list;
    QList<QAction*> actions = this->actions();

    foreach(QAction *action, actions) {
        if(action->isSeparator()) {
            list.append("Separator");
            continue;
        }
        list.append(action->text());
    }
    return list;
}


