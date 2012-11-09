
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

class DlgSettings;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    void createMenusAndToolbars();

    AppSettings *m_settings;
    DlgSettings *m_settingsDialog;
    QHash<QString, QMenu*> m_menus;
    QHash<QString, QtManagedToolBar* > m_toolbars;

};


}

#endif //__W_MAIN_WINDOW_H__
