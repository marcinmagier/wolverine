
#include "PageScintilla.h"
#include "ui_PageScintilla.h"

using namespace Wolverine::Settings;

PageScintilla::PageScintilla(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageScintilla)
{
    ui->setupUi(this);

    ui->checkBox->setChecked(settings->scintilla->getValBool());
    connect(ui->checkBox, SIGNAL(clicked(bool)), settings->scintilla, SLOT(setValBool(bool)));
    connect(settings->scintilla, SIGNAL(valBoolChanged(bool)), ui->checkBox_2, SLOT(setChecked(bool)));
}

PageScintilla::~PageScintilla()
{
    delete ui;
}
