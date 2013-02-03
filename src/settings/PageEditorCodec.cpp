

#include "PageEditorCodec.h"
#include "ui_PageEditorCodec.h"

#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"


#include <QStringList>
#include <QTextCodec>


using namespace Wolverine::Settings;

PageEditorCodec::PageEditorCodec(AppSettings *settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageEditorCodec)
{
    mSettings = settings;
    ui->setupUi(this);

    QStringList codecsEnabled = settings->scintilla->getCodecAvailable();
    foreach(const QByteArray &name, QTextCodec::availableCodecs()) {
        QListWidgetItem *item = new QListWidgetItem(name, ui->listCodecs);
        if(codecsEnabled.contains(name)) {
            item->setCheckState(Qt::Checked);
        } else {
            item->setCheckState(Qt::Unchecked);
        }
        ui->listCodecs->addItem(item);
    }

    connect(ui->listCodecs, SIGNAL(itemClicked(QListWidgetItem*)),
                      this, SLOT(onItemClicked(QListWidgetItem*)) );
    connect(ui->btnCheckAll, SIGNAL(clicked()),
                       this, SLOT(onSelectAll()) );
    connect(ui->btnUcheckAll, SIGNAL(clicked()),
                        this, SLOT(onUnselectAll()) );
}

PageEditorCodec::~PageEditorCodec()
{
    delete ui;
}


void PageEditorCodec::onItemClicked(QListWidgetItem *item)
{
    if(item) {
        if(item->checkState() == Qt::Checked) {
            item->setCheckState(Qt::Unchecked);
            mSettings->scintilla->delCodecAvailable(item->text());
        } else {
            item->setCheckState(Qt::Checked);
            mSettings->scintilla->addCodecAvailable(item->text());
        }
    }
}

void PageEditorCodec::onSelectAll()
{
    for(int i=0; i<ui->listCodecs->count(); i++) {
        QListWidgetItem *item = ui->listCodecs->item(i);
        item->setCheckState(Qt::Checked);
        mSettings->scintilla->addCodecAvailable(item->text());
    }
}

void PageEditorCodec::onUnselectAll()
{
    for(int i=0; i<ui->listCodecs->count(); i++) {
        QListWidgetItem *item = ui->listCodecs->item(i);
        item->setCheckState(Qt::Unchecked);
        mSettings->scintilla->delCodecAvailable(item->text());
    }
}
