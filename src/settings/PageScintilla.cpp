
#include "PageScintilla.h"
#include "ui_PageScintilla.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"



using namespace Wolverine::Settings;

PageScintilla::PageScintilla(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageScintilla)
{
    ui->setupUi(this);


}

PageScintilla::~PageScintilla()
{
    delete ui;
}
