
#include "PageEditor.h"
#include "ui_PageEditor.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"



using namespace Wolverine::Settings;

PageEditor::PageEditor(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageEditor)
{
    ui->setupUi(this);


}

PageEditor::~PageEditor()
{
    delete ui;
}
