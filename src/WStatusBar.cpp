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
#include "WEditorBinder.h"
#include "WEditorLexerManager.h"
#include "WActionManager.h"
#include "CfgAppSettings.h"
#include "CfgScintillaSettings.h"

#include "qtlabel.h"
#include "Logger.h"

#include <QCursor>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QMainWindow>

#include <QDebug>


#define WINDOW_TITLE_PATTERN    "%1 - Wolverine"

#define STATUS_LABEL_STYLE      "QLabel {"                  \
                                "padding-left: 4px;"        \
                                "padding-right: 4px;"       \
                                "font-size: 8pt;"           \
                                "}"

#define FILE_STATISTICS_PATTERN     "length: %1     lines: %2"
#define POSITION_PATTERN            "Ln: %1     Col: %2     Sel: 0 | 0"


using namespace Wolverine;



static QIcon getEoLIcon(Editor::EolMode eol);

QIcon getEoLIcon(Editor::EolMode eol)
{
    switch(eol) {
        case Editor::EolWindows :
            return QIcon(":/eol_win.png");
        case Editor::EolMac :
            return QIcon(":/eol_mac.png");
        case Editor::EolUnix :
            return QIcon(":/eol_unix.png");
    }
    LOG_ERROR("EoL not known");
    return QIcon();
}




StatusBar::StatusBar(QWidget *parent) :
    QStatusBar(parent)
{
    mMainWindow = dynamic_cast<QMainWindow*>(parent);
    mEditorProxy = EditorProxy::instance();

    mLblFilePath = new QtLabel("");
    mLblFilePath->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblFilePath->setMinimumWidth(50);
    mLblFilePath->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    this->addPermanentWidget(mLblFilePath, 2);

    mLblFileStatistics = new QtLabel();
    mLblFileStatistics->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblFileStatistics->setMinimumWidth(160);
    this->addPermanentWidget(mLblFileStatistics);

    mLblPosition = new QtLabel();
    mLblPosition->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblPosition->setMinimumWidth(180);
    this->addPermanentWidget(mLblPosition);

    mLblCodec = new QtLabel();
    mLblCodec->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblCodec->setMinimumWidth(110);
    connect(mLblCodec, SIGNAL(clickedLong(Qt::MouseButton)),
                 this, SLOT(onLblCodecClickLong(Qt::MouseButton)) );
    this->addPermanentWidget(mLblCodec);

    mLblLexer = new QtLabel();
    mLblLexer->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblLexer->setMinimumWidth(100);
    connect(mLblLexer, SIGNAL(clickedLong(Qt::MouseButton)),
                 this, SLOT(onLblLexerClickLong(Qt::MouseButton)) );
    this->addPermanentWidget(mLblLexer);

    mLblEoL = new QtLabel();
    mLblEoL->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblEoL->setPixmap(getEoLIcon(Editor::EolUnix).pixmap(15, 15));
    connect(mLblEoL, SIGNAL(clickedLong(Qt::MouseButton)),
               this, SLOT(onLblEoLClickLong(Qt::MouseButton)) );
    this->addPermanentWidget(mLblEoL);

    mLblInsOvr = new QtLabel("INS");
    mLblInsOvr->setStyleSheet(QString(STATUS_LABEL_STYLE));
    mLblInsOvr->setMinimumWidth(40);
    connect(mLblInsOvr, SIGNAL(doubleClicked(Qt::MouseButton)),
                  this, SLOT(onLblInsOvrDoubleClick(Qt::MouseButton)) );
    this->addPermanentWidget(mLblInsOvr);


    connect(mEditorProxy, SIGNAL(currentEditorChanged(Editor*)),
                      this, SLOT(onCurrentEditorChanged(Editor*)) );
    onCurrentEditorChanged(mEditorProxy->getCurrentEditor());
}




void StatusBar::onCurrentEditorChanged(Editor *editor)
{
    if(editor == 0)
        return;

    EditorBinder *binder = editor->getBinder();
    onCurrentEditorFileInfoChanged(binder);

    mLblCodec->setText(editor->getCode());
    mLblLexer->setText(binder->getLexerName());

    connect(editor, SIGNAL(cursorPositionChanged(int,int)),
              this, SLOT(onCurrentEditorPosChanged(int,int)), Qt::UniqueConnection );
    connect(editor, SIGNAL(textChanged()),
              this, SLOT(onCurrentEditorTextChanged()), Qt::UniqueConnection );
    connect(editor, SIGNAL(selectionChanged()),
              this, SLOT(onCurrentEditorSelectionChanged()), Qt::UniqueConnection );
    connect(binder, SIGNAL(fileInfoChanged(QFileInfo*)),
              this, SLOT(onCurrentEditorFileInfoChanged(QFileInfo*)), Qt::UniqueConnection );
    connect(binder, SIGNAL(lexerChanged(QString)),
              this, SLOT(onCurrentEditorLexerChanged(QString)), Qt::UniqueConnection );
    connect(binder, SIGNAL(eolChanged(Editor::EolMode)),
              this, SLOT(onCurrentEditorEolChanged(Editor::EolMode)), Qt::UniqueConnection );

    QPoint pos = editor->pos();
    onCurrentEditorPosChanged(pos.x(), pos.y());
    onCurrentEditorTextChanged();
    onCurrentEditorEolChanged(binder->getEolMode());


    ActionManager *actionManager = ActionManager::instance();
    QAction *action = actionManager->getAction(W_ACTION_GROUP_VIEW, W_ACTION_MONITOR_MODE);
    disconnect(action, SIGNAL(toggled(bool)), 0, 0);
    action->setChecked(binder->isMonitorModeEnabled());
    connect( action, SIGNAL(toggled(bool)),
             binder, SLOT(enableMonitorMode(bool)) );

    action = actionManager->getAction(W_ACTION_GROUP_FILE, W_ACTION_RELOAD);
    action->setEnabled(binder->exists());
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
   // qDebug() << "Selection changed";
}

void StatusBar::onCurrentEditorFileInfoChanged(QFileInfo *fileinfo)
{
    QString filePath = fileinfo->canonicalFilePath();
    if(filePath.length() > 0)
        mLblFilePath->setText(filePath);
    else
        mLblFilePath->setText(fileinfo->fileName());
    mMainWindow->setWindowTitle( QString(WINDOW_TITLE_PATTERN).arg(fileinfo->fileName()) );
}

void StatusBar::onCurrentEditorLexerChanged(const QString &name)
{
    mLblLexer->setText(name);
}

void StatusBar::onCurrentEditorEolChanged(QsciScintilla::EolMode eolMode)
{
    mLblEoL->setPixmap(getEoLIcon(eolMode).pixmap(15, 15));
}



void StatusBar::onLblCodecClickLong(Qt::MouseButton /*button*/)
{
    Editor *editor = mEditorProxy->getCurrentEditor();
    QString currCodec = editor->getCode();
    QMenu menu(this);

    QAction *action;
    foreach(const QString &name, AppSettings::instance()->scintilla->getCodecAvailable()) {
        action = menu.addAction(name);
        action->setCheckable(true);
        if(name == currCodec)
            action->setChecked(true);
    }

    action = menu.exec(QCursor::pos());
    if(action == 0)
        return;

    action->setChecked(true);
    currCodec = action->text();
    mLblCodec->setText(currCodec);
    editor->setCodec(currCodec);
}


void StatusBar::onLblLexerClickLong(Qt::MouseButton /*button*/)
{
    Editor *editor = mEditorProxy->getCurrentEditor();
    EditorBinder *binder = editor->getBinder();
    QList<QString> lexNames = EditorLexerManager::instance()->getLexerNames();
    QString currLexName = binder->getLexerName();
    QMenu menu(this);

    QAction *action;
    foreach(const QString &name, lexNames) {
        action = menu.addAction(name);
        action->setCheckable(true);
        if(name == currLexName)
            action->setChecked(true);
    }

    action = menu.exec(QCursor::pos());
    if(action == 0)
        return;

    action->setChecked(true);
    currLexName = action->text();
    mLblLexer->setText(currLexName);
    binder->setLexer(currLexName);
}

void StatusBar::onLblEoLClickLong(Qt::MouseButton /*button*/)
{
    QAction *action;
    QMenu menu(this);
    Editor::EolMode oldEolMode = mEditorProxy->getCurrentEditor()->eolMode();

    action = menu.addAction(QIcon(":/eol_win.png"), QString("Win"));
    action->setData( static_cast<int>(Editor::EolWindows));
    action->setCheckable(true);
    if(oldEolMode == Editor::EolWindows) {
        action->setChecked(true);
    }

    action = menu.addAction(QIcon(":/eol_mac.png"), QString("Mac"));
    action->setData( static_cast<int>(Editor::EolMac));
    action->setCheckable(true);
    if(oldEolMode == Editor::EolMac) {
        action->setChecked(true);
    }

    action = menu.addAction(QIcon(":/eol_unix.png"), QString("Unix"));
    action->setData( static_cast<int>(Editor::EolUnix));
    action->setCheckable(true);
    if(oldEolMode == Editor::EolUnix) {
        action->setChecked(true);
    }

    action = menu.exec(QCursor::pos());
    if(action == 0)
        return;

    Editor::EolMode newEolMode = static_cast<Editor::EolMode>(action->data().toInt());
    if(oldEolMode != newEolMode) {
        //mLblEoL->setPixmap(action->icon().pixmap(15, 15));
        mEditorProxy->getCurrentEditor()->getBinder()->setEolMode(newEolMode);
    }
}

void StatusBar::onLblInsOvrDoubleClick(Qt::MouseButton /*button*/)
{
    Editor *edit = mEditorProxy->getCurrentEditor();
    if(mLblInsOvr->text() == "INS") {
        mLblInsOvr->setText("OVR");
        edit->setOverwriteMode(true);
    } else {
        mLblInsOvr->setText("INS");
        edit->setOverwriteMode(false);
    }
}
