
#include "AppConfig.h"
#include "qtmanagedtoolbar.h"

#include <QApplication>
#include <QMainWindow>
#include <QtGui>


class Toolbar : public QtManagedToolBar
{
public:
    Toolbar(QWidget *parent, QString toolbarName):
        QtManagedToolBar(parent, toolbarName){};
    void contextMenuEvent(QContextMenuEvent *);
};

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
    app.setApplicationName("Wolverine");

    AppConfig *settings = AppConfig::instance();
    settings->loadConfiguration();
    settings->saveConfiguration();

    QMainWindow mainWin;
    mainWin.resize(800, 600);
    Toolbar *toolbar = new Toolbar(&mainWin, "MainToolbar");
    QAction *action2 = new QAction("Cut", &mainWin);
    action2->setIcon(QIcon(":/cut.png"));
    toolbar->addAction(action2);

    QAction *action1 = new QAction("Find", &mainWin);
    action1->setIcon(QIcon(":/find.png"));
    toolbar->addAction(action1);

    action1 = new QAction("Paste", &mainWin);
    action1->setIcon(QIcon(":/paste.png"));
    toolbar->addAction(action1);

    QSpinBox *spin = new QSpinBox(toolbar);
    action1 = toolbar->addWidget(spin);
    action1->setText("SpinBox");

    toolbar->restoreConfig();
    toolbar->saveConfig();

    mainWin.addToolBar(toolbar);
    //toolbar->setManagerEnabled(false);
    mainWin.show();
    return app.exec();
}
