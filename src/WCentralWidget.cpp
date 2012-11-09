
#include "WCentralWidget.h"
#include "WDocument.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QTabWidget>



using namespace Wolverine;


CentralWidget::CentralWidget(QWidget *parent):
    QWidget(parent)
{

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    panelLeft = new QTabWidget(splitter);
    panelRight = new QTabWidget(splitter);
    panelRight->hide();
    splitter->addWidget(panelLeft);
    splitter->addWidget(panelRight);
    layout->addWidget(splitter);

    editor = new Document();
    panelLeft->addTab(editor, "New");
}

CentralWidget::~CentralWidget()
{

}
