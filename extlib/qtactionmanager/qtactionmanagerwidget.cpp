
#include "qtactionmanagerwidget.h"
#include "ui_qtactionmanagerwidget.h"

QtActionManagerWidget::QtActionManagerWidget(QtActionManager *actionManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtActionManagerWidget),
    m_actionManager(actionManager)
{
    ui->setupUi(this);

    ui->cmbSchemes->addItem(m_actionManager->m_currentScheme);

    QStringList headers;
    headers << tr("Command") << tr("Binding") << tr("Category");
    ui->treeActions->setHeaderLabels(headers);


    foreach(QString category, m_actionManager->m_actionCategories.keys()) {
        QListQtActions qtactions = m_actionManager->m_actionCategories.value(category);

        for(int i=0; i<qtactions.length(); ++i) {
            QAction *action = qtactions[i].action;
            QStringList row;
            row << action->text() << action->shortcut().toString() << category;
            QTreeWidgetItem *item = new QTreeWidgetItem(row);
            ui->treeActions->addTopLevelItem(item);
        }
    }
}

QtActionManagerWidget::~QtActionManagerWidget()
{
    delete ui;
}
