

#include "DlgSettings.h"
#include "CfgAppSettings.h"
#include "WActionManager.h"
#include "WEditorLexerManager.h"

#include "PageGeneral.h"
#include "PageEditor.h"
#include "PageEditorCodec.h"
#include "PageView.h"

#include <QIcon>

using namespace Wolverine;



DlgSettings::DlgSettings(QWidget *parent) :
    QtDialogSettings(AppSettings::instance(), parent),
    mSettings(AppSettings::instance()),
    mActionManager(ActionManager::instance()),
    mLexerManager(EditorLexerManager::instance())
{
    this->setWindowTitle(tr("Wolverine Settings"));
    this->setWindowIcon(QIcon(":/settings.png"));
}

void DlgSettings::showDialog()
{
    Settings::PageGeneral *general = new Settings::PageGeneral(mSettings, this);
    addSettingsPage(tr("General"), general);

    Settings::PageView *view = new Settings::PageView(mSettings, this);
    addSettingsPage(tr("View"), view);

    Settings::PageEditor *editor = new Settings::PageEditor(mSettings, this);
    addSettingsPage(tr("Editor"), editor);

    Settings::PageEditorCodec *editorCodecs = new Settings::PageEditorCodec(mSettings, this);
    addSettingsPage(tr("Codecs"), tr("Editor"), editorCodecs);

    QWidget *lexerManagerWidget = mLexerManager->getLexerManagerWidget(this);
    addSettingsPage(tr("Lexers"), tr("Editor"), lexerManagerWidget);

    QWidget *actionManagerWidget = mActionManager->getActionManagerWidget(this);
    addSettingsPage(tr("Key Binding"), actionManagerWidget);

    // Just call exec(). QtDialogSettings is responsible for calling correct inform functions.
    if(QtDialogSettings::exec()) {
        mSettings->saveConfiguration();
        mActionManager->saveConfig();
        mLexerManager->saveConfig();
    }

    // There is no need to keep these variables in memory.
    clearPages();
    delete general;
    delete editor;
    delete editorCodecs;
    delete view;
    delete actionManagerWidget;
    delete lexerManagerWidget;
}


void DlgSettings::informToDropBackup()
{
    //Inform all external settings managers to throw backup.
    //Every internal pages works on AppSettings that does it automatically.
    mActionManager->dropConfigurationBackup();
    mLexerManager->dropConfigurationBackup();
}

void DlgSettings::informToCreateNewBackup()
{
    //Inform all external settings managers to create fresh backup (drop the previous one).
    //Every internal pages works on AppSettings that does it automatically.
    mActionManager->createConfigurationBackup();
    mLexerManager->createConfigurationBackup();
}

void DlgSettings::informToRestoreBackup()
{
    //Inform all external settings managers to apply configuration backup.
    //Every internal pages works on AppSettings that does it automatically.
    mActionManager->restoreConfigurationBackup();
    mLexerManager->restoreConfigurationBackup();
}


