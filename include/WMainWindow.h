
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

    void openNewFile();

public slots:
    void openFile(const QString &file);
    void addDockWidget(QDockWidget *widget, Qt::DockWidgetArea area);
    void showDockWidget(QDockWidget *widget, Qt::DockWidgetArea area, const QString &title);
    void tabifyDockWidget(QDockWidget *widget, QDockWidget *to, const QString &title);

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
    QHash<QString, QDockWidget*> mDocks;
    QList<QDockWidget*> mDockWidgets;

    CentralWidget *mCentralWidget;
    EditorProxy *mEditorProxy;
    Finder *mFinder;
    DockWidget *mMiniMap;

};


}

#endif //__W_MAIN_WINDOW_H__
