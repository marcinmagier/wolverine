
#include "qtdialogsettings.h"
#include "ui_qtdialogsettings.h"

#include <QCloseEvent>



QtDialogSettings::QtDialogSettings(QtConfig *config, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDialogSettings),
    m_config(config)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(ok()));
    connect(ui->btnApply, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

    connect(ui->treePages, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(changeCurrentPage(QTreeWidgetItem*,QTreeWidgetItem*)));
}

QtDialogSettings::~QtDialogSettings()
{
    delete ui;
}


void QtDialogSettings::accept()
{
     //Create fresh backup (drop the previous one)
    m_config->createConfigurationBackup();
    emit applied();
}

void QtDialogSettings::ok()
{
    m_config->dropConfigurationBackup();
    QDialog::accept();
}

void QtDialogSettings::reject()
{
     //Retrieve previous configuration and leave
    m_config->restoreConfigurationBackup();
    QDialog::reject();
}

int QtDialogSettings::exec()
{
    m_config->createConfigurationBackup();
    return QDialog::exec();
}


void QtDialogSettings::closeEvent(QCloseEvent *e)
{
    //Retrieve previous configuration and leave
   m_config->restoreConfigurationBackup();
   e->accept();
}


void QtDialogSettings::addSettingsPage(const QString &name, QWidget *page)
{
    int idx = ui->stackedPages->addWidget(page);
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(name));
    m_pageMap[item] = idx;
    ui->treePages->addTopLevelItem(item);
}

void QtDialogSettings::addSettingsPage(const QString &name, const QString &parent, QWidget *page)
{
    QList<QTreeWidgetItem*> items = ui->treePages->findItems(parent, Qt::MatchFixedString);

    if(items.isEmpty())
        return;

    QTreeWidgetItem *parentItem = items[0];
    QTreeWidgetItem *item = new QTreeWidgetItem(parentItem, QStringList(name));
    int idx = ui->stackedPages->addWidget(page);
    m_pageMap[item] = idx;
    parentItem->setExpanded(true);
}

void QtDialogSettings::changeCurrentPage( QTreeWidgetItem * current, QTreeWidgetItem *)
{
    int idx = m_pageMap[current];
    ui->stackedPages->setCurrentIndex(idx);
}

