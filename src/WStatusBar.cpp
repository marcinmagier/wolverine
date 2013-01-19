/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       WStatusBar.cpp
 *  @brief      Wolverine::StatusBar class implementation.
 */


#include "WStatusBar.h"
#include "WEditor.h"
#include "WEditorProxy.h"
#include "CfgAppSettings.h"

#include "qtlabel.h"

#include <QLabel>

#include <QDebug>


#define STATUS_LABEL_STYLE      "QLabel {"                  \
                                "padding-left: 4px;"        \
                                "padding-right: 4px;"       \
                                "}"

#define FILE_STATISTICS_PATTERN     "length: %1     lines: %2"
#define POSITION_PATTERN            "Ln: %1     Col: %2     Sel: 0 | 0"

using namespace Wolverine;


StatusBar::StatusBar(EditorProxy *currentEditor, QWidget *parent) :
    QStatusBar(parent),
    mEditorProxy(currentEditor)
{
    mLblPosition = new QtLabel();
    mLblPosition->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblPosition->setMinimumWidth(180);
    this->addPermanentWidget(mLblPosition);

    mLblFilePath = new QtLabel("/test/file/path");
    mLblFilePath->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addPermanentWidget(mLblFilePath, 2);

    mLblFileStatistics = new QtLabel();
    mLblFileStatistics->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblFileStatistics->setMinimumWidth(160);
    this->addPermanentWidget(mLblFileStatistics);

    mLblCodec = new QtLabel("ANSI");
    mLblCodec->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addPermanentWidget(mLblCodec);

    mLblLexer = new QtLabel("C++");
    mLblLexer->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addPermanentWidget(mLblLexer);

    mLblEoL = new QtLabel("WINDOWS");
    mLblEoL->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addPermanentWidget(mLblEoL);

    mLblInsOvr = new QtLabel("INS");
    mLblInsOvr->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addPermanentWidget(mLblInsOvr);


    connect(mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                      this, SLOT(onCurrentEditorChanged(Editor*)) );
    onCurrentEditorChanged(mEditorProxy->getCurrentEditor());
}




void StatusBar::onCurrentEditorChanged(Editor *editor)
{
    QString filePath = editor->getFilePath();
    if(filePath.length() > 0)
        mLblFilePath->setText(editor->getFilePath());
    else
        mLblFilePath->setText(tr("New"));

    connect(editor, SIGNAL(cursorPositionChanged(int,int)),
              this, SLOT(onCurrentEditorPosChanged(int,int)), Qt::UniqueConnection );
    connect(editor, SIGNAL(textChanged()),
              this, SLOT(onCurrentEditorTextChanged()), Qt::UniqueConnection );
    connect(editor, SIGNAL(selectionChanged()),
            this, SLOT(onCurrentEditorSelectionChanged()), Qt::UniqueConnection );

    QPoint pos = editor->pos();
    onCurrentEditorPosChanged(pos.x(), pos.y());
    onCurrentEditorTextChanged();
}


void StatusBar::onCurrentEditorPosChanged(int line, int column)
{
    mLblPosition->setText(QString(POSITION_PATTERN).arg(line)
                                                   .arg(column) );
}

void StatusBar::onCurrentEditorTextChanged()
{
    Editor *editor = mEditorProxy->getCurrentEditor();
    mLblFileStatistics->setText(QString(FILE_STATISTICS_PATTERN).arg(editor->length())
                                                                .arg(editor->lines()) );
}

void StatusBar::onCurrentEditorSelectionChanged()
{
    qDebug() << "Selection changed";
}
