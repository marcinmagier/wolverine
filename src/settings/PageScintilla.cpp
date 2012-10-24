
#include "PageScintilla.h"
#include "ui_PageScintilla.h"

using namespace Wolverine::Settings;

PageScintilla::PageScintilla(CfgAppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageScintilla)
{
    ui->setupUi(this);

    connect(ui->checkBox, SIGNAL(clicked(bool)), &settings->scintilla, SLOT(setValBool(bool)));
}

PageScintilla::~PageScintilla()
{
    delete ui;
}
