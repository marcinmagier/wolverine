
#ifndef __W_MAIN_WINDOW_H__
 #define __W_MAIN_WINDOW_H__

#include <QMainWindow>


class CfgAppSettings;
class QtActionManager;


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

    CfgAppSettings *m_settings;
    DlgSettings *m_settingsDialog;
    QtActionManager *m_actionManager;

};


}

#endif //__W_MAIN_WINDOW_H__
