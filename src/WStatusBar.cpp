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



using namespace Wolverine;


StatusBar::StatusBar(EditorProxy *currentEditor, QWidget *parent) :
    QStatusBar(parent),
    mCurrentEditor(currentEditor)
{
    connect(mCurrentEditor, SIGNAL(currentEditorChanged(Editor*)),
                      this, SLOT(onCurrentEditorChanged(Editor*)) );



    mLblFilePath = new QtLabel("/test/file/path");
    mLblFilePath->setStyleSheet(QString(STATUS_LABEL_STYLE));
    connect(mLblFilePath, SIGNAL(clicked(QMouseEvent*)),
            this, SLOT(onClicked(QMouseEvent*)) );
    connect(mLblFilePath, SIGNAL(clickedLong(QMouseEvent*)),
            this, SLOT(onClickedLong(QMouseEvent*)) );
    connect(mLblFilePath, SIGNAL(doubleClicked(QMouseEvent*)),
            this, SLOT(onDoubleClicked(QMouseEvent*)) );
    this->addWidget(mLblFilePath, 2);

    mLblFileStatistics = new QLabel("length: 36     lines: 8");
    mLblFileStatistics->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addWidget(mLblFileStatistics);

    mLblPosition = new QLabel("Ln: 5     Col: 9     Sel: 0 | 0");
    mLblPosition->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addWidget(mLblPosition);

    mLblCodec = new QLabel("ANSI");
    mLblCodec->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addWidget(mLblCodec);

    mLblLexer = new QLabel("C++");
    mLblLexer->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addWidget(mLblLexer);

    mLblEoL = new QLabel("WINDOWS");
    mLblEoL->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addWidget(mLblEoL);

    mLblInsOvr = new QLabel("INS");
    mLblInsOvr->setStyleSheet(QString(STATUS_LABEL_STYLE));
    this->addWidget(mLblInsOvr);
}




void StatusBar::onCurrentEditorChanged(Editor *editor)
{

}

void StatusBar::onClicked(QMouseEvent *event)
{
    qDebug() << "Clicked";
}

void StatusBar::onClickedLong(QMouseEvent *event)
{
    qDebug() << "Clicked long";
}

void StatusBar::onDoubleClicked(QMouseEvent *event)
{
    qDebug() << "Double clicked";
}

