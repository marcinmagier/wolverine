
#include "PageEditor.h"
#include "ui_PageEditor.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"

#include "qtscintilla.h"



using namespace Wolverine::Settings;

PageEditor::PageEditor(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageEditor),
    mSettings(settings)
{
    ui->setupUi(this);

    if(settings->scintilla->getWhiteSpaceVisibleMode() == QsciScintilla::WsVisibleAfterIndent)
        ui->radioVisibleAfterIndent->setChecked(true);
    else
        ui->radioVisibleAlways->setChecked(true);

    if(settings->scintilla->getWrapMode() == QsciScintilla::WrapCharacter)
        ui->radioCharBound->setChecked(true);
    else
        ui->radioWordBound->setChecked(true);

    connect( ui->radioVisibleAfterIndent, SIGNAL(clicked()),
                                    this, SLOT(onRadioVisibleAfterIndentClicked()) );
    connect( ui->radioVisibleAlways, SIGNAL(clicked()),
                               this, SLOT(onRadioVisibleAlwaysClicked()) );
    connect( ui->radioCharBound, SIGNAL(clicked()),
                           this, SLOT(onRadioWrapCharBoundClicked()) );
    connect( ui->radioWordBound, SIGNAL(clicked()),
                           this, SLOT(onRadioWrapWordBoundClicked()) );
}

PageEditor::~PageEditor()
{
    delete ui;
}


void PageEditor::onRadioVisibleAfterIndentClicked()
{
    mSettings->scintilla->setWhiteSpaceVisibleMode(QsciScintilla::WsVisibleAfterIndent);
}

void PageEditor::onRadioVisibleAlwaysClicked()
{
    mSettings->scintilla->setWhiteSpaceVisibleMode(QsciScintilla::WsVisible);
}

void PageEditor::onRadioWrapCharBoundClicked()
{
    mSettings->scintilla->setWrapMode(QsciScintilla::WrapCharacter);
}

void PageEditor::onRadioWrapWordBoundClicked()
{
    mSettings->scintilla->setWrapMode(QsciScintilla::WrapWord);
}
