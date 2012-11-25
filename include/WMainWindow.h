
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



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();


public slots:
    void openFile(const QString &file);


private:
    void createMenusAndToolbars();


    AppSettings *mSettings;
    ActionManager *mActionManager;
    DlgSettings *mSettingsDialog;
    QHash<QString, QMenu*> mMenus;
    QHash<QString, QtManagedToolBar* > mToolbars;

};


}

#endif //__W_MAIN_WINDOW_H__
