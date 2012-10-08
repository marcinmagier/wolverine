#include "qtmanagedtoolbar.h"

#include <QApplication>
#include <QMainWindow>
#include <QtGui>


class Toolbar : public QtManagedToolBar
{
public:
    Toolbar(QWidget *parent):
        QtManagedToolBar(parent){};
    void contextMenuEvent(QContextMenuEvent *);
};


// Example of context menu 
// QtManagedToolBar adds additional item "Customize" to the context menu so we have to do it in this way
// Additional item "Customize" is added only if manager is enabled - setManagerEnabled()
void Toolbar::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu(this);
    menu->addAction(tr("TestAction"));
    menu->addAction(tr("TestAction2"));
    menu->addSeparator();

    showContextMenu(event, menu);

    delete menu;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("ManagedToolbarExample");

    QMainWindow mainWin;
    Toolbar *toolbar = new Toolbar(&mainWin);
    QAction *action = new QAction("Action1", &mainWin);
    action->setIcon(QIcon(":/action1.png"));
    toolbar->addAction(action);

    action = new QAction("Action2", &mainWin);
    action->setIcon(QIcon(":/action2.png"));
    toolbar->addAction(action);

    action = new QAction("Action3", &mainWin);
    action->setIcon(QIcon(":/action3.png"));
    toolbar->addAction(action);
	
	//At the end we should call restoreConfig to let QtManagedToolBar customize items
    toolbar->restoreConfig();

	//If we don't want to show "Customize" in context menu we can disable it
	//toolbar->setManagerEnabled(false);
	
    mainWin.addToolBar(toolbar);
    mainWin.show();
    return app.exec();
}
