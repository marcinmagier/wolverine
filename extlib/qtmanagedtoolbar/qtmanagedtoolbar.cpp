
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
    mToolbarName = name;
    mActionsAvailable.clear();
    mIsManagerEnabled = true;
}




void QtManagedToolBar::addAction(const QString &name, QAction *action)
{
    addActionAvailable(name, action);
    QToolBar::addAction(action);
}

QAction* QtManagedToolBar::addWidget(const QString &name, QWidget *widget)
{
    QAction *tmp = QToolBar::addWidget(widget);
    addActionAvailable(name, tmp);
    return tmp;
}

void QtManagedToolBar::removeAction(QAction *action)
{
    QString key = mActionsAvailable.key(action);
    if(!key.isEmpty()) {
        mActionsAvailable.remove(key);
        QToolBar::removeAction(action);
    }
}

void QtManagedToolBar::removeAction(const QString &name)
{
    if(mActionsAvailable.contains(name)) {
        QAction *action = mActionsAvailable[name];
        mActionsAvailable.remove(name);
        QToolBar::removeAction(action);
    }
}





void QtManagedToolBar::contextMenuEvent(QContextMenuEvent *event)
{
    if(mIsManagerEnabled) {
        QMenu *contextMenu = new QMenu(this);
        QAction *action = contextMenu->addAction(tr("Customize"));
        action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
        connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));

        contextMenu->exec(event->globalPos());

        delete contextMenu;
        //check if action is deleted
    }
}

void QtManagedToolBar::showContextMenu(QContextMenuEvent *event, QMenu *menu)
{
	if(mIsManagerEnabled) {
		QAction *action = menu->addAction(tr("Customize"));
		action->setIcon(QIcon(QT_MANAGEDTOOLBAR_ICON_CUSTOMIZE));
		connect(action, SIGNAL(triggered()), this, SLOT(showManagerDialog()));
	}

	menu->exec(event->globalPos());
}



void QtManagedToolBar::showManagerDialog()
{
    QtManagedToolBarDialog dlg(this);
    QStringList tmpActionsVisible = createConfiguration();

    if(dlg.exec(&mActionsAvailable, &tmpActionsVisible)) {
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

    qset.setValue(mToolbarName, QVariant::fromValue(actionList));
}

void QtManagedToolBar::restoreConfig()
{

    QSettings qset(QSettings::IniFormat, QSettings::UserScope, qApp->applicationName(), "toolbars");
    QVariant var = qset.value(mToolbarName);
    QStringList list = var.toStringList();

    applyConfiguration(list);
}




void QtManagedToolBar::addActionAvailable(const QString &name, QAction *action)
{
    if(action->text().isEmpty())
        action->setText( defItemName + QString::number(defItemCount++) );
    mActionsAvailable[name] = action;
}

void QtManagedToolBar::applyConfiguration(const QStringList &config)
{
    if(config.size() == 0)
        return;

    clear();
    foreach(QString name, config) {
        if(name == "Separator") {
            QToolBar::addSeparator();
            continue;
        }
        if(mActionsAvailable.contains(name))
            QToolBar::addAction(mActionsAvailable[name]);
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
        QString name = mActionsAvailable.key(action);
        if(!name.isEmpty())
            list.append(name);
    }
    return list;
}


