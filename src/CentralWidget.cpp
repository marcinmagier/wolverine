
#include "WCentralWidget.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QTabWidget>


#include "Qsci/qsciscintilla.h"



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

    editor = new QsciScintilla();
    panelLeft->addTab(editor, "New");
}

CentralWidget::~CentralWidget()
{

}
