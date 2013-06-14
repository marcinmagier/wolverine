
#ifndef __W_MAIN_WINDOW_H__
 #define __W_MAIN_WINDOW_H__

class AppSettings;
class QtManagedToolBar;


class QString;
class QMenu;
class QDockWidget;

#include <QMainWindow>
#include <QHash>




namespace Wolverine
{

class ActionManager;
class DlgSettings;
class StatusBar;
class CentralWidget;
class Editor;
class EditorProxy;
class Finder;
class DockWidget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void addDockWidget(QDockWidget *widget);
    void addDockWidget(QDockWidget *widget, Qt::DockWidgetArea area);
    void addDockWidget(QDockWidget *widget, QDockWidget *tabifyTo);

    void openNewFile();


public slots:
    void openFile(const QString &file);


protected:
    virtual void closeEvent(QCloseEvent *event);


private slots:
    void onAppCustimizeEnabledChanged(bool enabled);
    void onDockTopLevelChanged(bool topLevel);


private:
    void createMenusAndToolbars();
    void createDocks();


    AppSettings *mSettings;
    ActionManager *mActionManager;
    DlgSettings *mSettingsDialog;
    QHash<QString, QMenu*> mMenus;
    QHash<QString, QtManagedToolBar*> mToolbars;
    QList<QDockWidget*> mDocks;

    CentralWidget *mCentralWidget;
    EditorProxy *mEditorProxy;
    Finder *mFinder;

};


}

#endif //__W_MAIN_WINDOW_H__
