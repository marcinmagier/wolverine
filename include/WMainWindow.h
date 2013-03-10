
#ifndef __W_MAIN_WINDOW_H__
 #define __W_MAIN_WINDOW_H__

class AppSettings;
class QtManagedToolBar;


class QString;
class QMenu;

#include <QMainWindow>
#include <QHash>




namespace Wolverine
{

class ActionManager;
class DlgSettings;
class StatusBar;
class CentralWidget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void openNewFile();

public slots:
    void openFile(const QString &file);

protected:
    virtual void closeEvent(QCloseEvent *);

private:
    void createMenusAndToolbars();


    AppSettings *mSettings;
    ActionManager *mActionManager;
    DlgSettings *mSettingsDialog;
    QHash<QString, QMenu*> mMenus;
    QHash<QString, QtManagedToolBar* > mToolbars;

    CentralWidget *mCentralWidget;

};


}

#endif //__W_MAIN_WINDOW_H__
