
#include "qtactionmanagerwidget.h"
#include "ui_qtactionmanagerwidget.h"

#include <QTreeWidgetItem>



QtActionManagerWidget::QtActionManagerWidget(QtActionManager *actionManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtActionManagerWidget),
    m_actionManager(actionManager)
{
    ui->setupUi(this);

    ui->cmbSchemes->addItems(m_actionManager->m_schemes);
    int idxCurrentScheme = m_actionManager->m_schemes.indexOf(m_actionManager->m_currentScheme);
    ui->cmbSchemes->setCurrentIndex(idxCurrentScheme);

    QStringList headers;
    headers << tr("Command") << tr("Binding") << tr("Category");
    ui->treeActions->setHeaderLabels(headers);

    updateUI();

    connect(ui->cmbSchemes, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeCurrentScheme(QString)));
}

QtActionManagerWidget::~QtActionManagerWidget()
{
    delete ui;
}


void QtActionManagerWidget::changeCurrentScheme(QString scheme)
{
    m_actionManager->m_currentScheme = scheme;
    ui->treeActions->clear();
    m_actionMap.clear();

    updateUI();
}


void QtActionManagerWidget::updateUI()
{
    QString scheme = m_actionManager->m_currentScheme;

    foreach(QString category, m_actionManager->m_actionCategories.keys()) {
        QtActionsList qtactions = m_actionManager->m_actionCategories.value(category);
        for(int i=0; i<qtactions.length(); ++i) {
            QAction *action = qtactions[i].action;
            QKeySequence shortcut = qtactions[i].schemeBinding[scheme];
            QStringList row;
            row << action->text() << shortcut << category;
            QTreeWidgetItem *item = new QTreeWidgetItem(row);
            item->setIcon(0, action->icon());
            ui->treeActions->addTopLevelItem(item);

            m_actionMap.insert(item, &qtactions[i]);
        }
    }
}
