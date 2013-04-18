/**************************************************************************************************
**
**  Copyright (C) 2012-2013 Magier Marcin
**
**  This program is free software: you can redistribute it and/or modify it under the terms
**  of the GNU General Public License as published by the Free Software Foundation,
**  either version 3 of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
**  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**  See the GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************************************/

/**
 *  @file       WFindReqWidget.cpp
 *  @brief      Wolverine::FindReqWidget class implementation.
 */


#include "WFindReqWidget.h"
#include "ui_WFindReqWidget.h"
#include "WFinder.h"

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"

#include "Logger.h"

#include <QLineEdit>


using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
FindReqWidget::FindReqWidget(Finder *finder, QWidget *parent) :
    QStackedWidget(parent),
    mFinder(finder),
    ui(new Ui::FindReqWidget)
{
    mGenSettings = AppSettings::instance()->general;

    ui->setupUi(this);

    connect( this, SIGNAL(currentChanged(int)),
             this, SLOT(onCurrentChanged(int)) );


    ui->btn0CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn0CaseSensitive->setToolTip(tr("Case Sensitive"));
    connect(ui->btn0CaseSensitive, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindCaseSensitive(bool)), Qt::DirectConnection);

    ui->btn1CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn1CaseSensitive->setToolTip(tr("Case Sensitive"));
    connect(ui->btn1CaseSensitive, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindCaseSensitive(bool)), Qt::DirectConnection);

    ui->btn2CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn2CaseSensitive->setToolTip(tr("Case Sensitive"));
    connect(ui->btn2CaseSensitive, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindCaseSensitive(bool)), Qt::DirectConnection);


    ui->btn0Words->setIcon(QIcon(":/search_words.png"));
    ui->btn0Words->setToolTip(tr("Whole Words"));
    connect(ui->btn0Words, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWholeWords(bool)), Qt::DirectConnection);

    ui->btn1Words->setIcon(QIcon(":/search_words.png"));
    ui->btn1Words->setToolTip(tr("Whole Words"));
    connect(ui->btn1Words, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWholeWords(bool)), Qt::DirectConnection);

    ui->btn2Words->setIcon(QIcon(":/search_words.png"));
    ui->btn2Words->setToolTip(tr("Whole Words"));
    connect(ui->btn2Words, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWholeWords(bool)), Qt::DirectConnection);


    ui->btn0Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn0Regexp->setToolTip(tr("Regular Expression"));
    connect(ui->btn0Regexp, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindRegexp(bool)), Qt::DirectConnection);

    ui->btn1Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn1Regexp->setToolTip(tr("Regular Expression"));
    connect(ui->btn1Regexp, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindRegexp(bool)), Qt::DirectConnection);

    ui->btn2Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn2Regexp->setToolTip(tr("Regular Expression"));
    connect(ui->btn2Regexp, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindRegexp(bool)), Qt::DirectConnection);


    ui->btn0Reverse->setIcon(QIcon(":/search_reverse.png"));
    ui->btn0Reverse->setToolTip(tr("Reverse Direction"));
    connect(ui->btn0Reverse, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindReverseDirection(bool)), Qt::DirectConnection);

    ui->btn1Reverse->setIcon(QIcon(":/search_reverse.png"));
    ui->btn1Reverse->setToolTip(tr("Reverse Direction"));
    connect(ui->btn1Reverse, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindReverseDirection(bool)), Qt::DirectConnection);


    ui->btn0Wrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btn0Wrap->setToolTip(tr("Wrap"));
    connect(ui->btn0Wrap, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWrap(bool)), Qt::DirectConnection);

    ui->btn1Wrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btn1Wrap->setToolTip(tr("Wrap"));
    connect(ui->btn1Wrap, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWrap(bool)), Qt::DirectConnection);


    ui->btn0InSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btn0InSelection->setToolTip(tr("In Selection"));
    connect(ui->btn0InSelection, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInSelection(bool)), Qt::DirectConnection);

    ui->btn1InSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btn1InSelection->setToolTip(tr("In Selection"));
    connect(ui->btn1InSelection, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInSelection(bool)), Qt::DirectConnection);


    ui->btn0Mark->setIcon(QIcon(":/search_mark.png"));
    ui->btn0Mark->setToolTip("Bookmark Line");
    connect(ui->btn0Mark, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindMark(bool)), Qt::DirectConnection);


    ui->btn2InSubDirs->setIcon(QIcon(":/search_subdirs.png"));
    ui->btn2InSubDirs->setToolTip(tr("Search in sub-folders"));
    connect(ui->btn2InSubDirs, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInSubDirs(bool)), Qt::DirectConnection);


    ui->btn2InHiddenDirs->setIcon(QIcon(":/search_hidden.png"));
    ui->btn2InHiddenDirs->setToolTip(tr("Search in hidden folders"));
    connect(ui->btn2InHiddenDirs, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInHiddenDirs(bool)), Qt::DirectConnection);


    ui->btn2SelectDir->setIcon(QIcon(":/search_select_dir.png"));
    ui->btn2SelectDir->setToolTip(tr("Select Directory"));

    ui->btn2CurrentDir->setIcon(QIcon(":/search_current_dir.png"));
    ui->btn2CurrentDir->setToolTip(tr("Select Current Document's Directory"));

    setupFindWidget();
}


/**
 *  Destructor
 */
FindReqWidget::~FindReqWidget()
{
    delete ui;
}


FindOptions FindReqWidget::getFindOptions()
{
    FindOptions opt;

    switch(currentIndex()) {
    case FindIdx:
        opt.findType = FindOptions::Find;
        opt.searchPattern = ui->cmb0SearchPattern->lineEdit()->text();
        break;

    case ReplaceIdx:
        opt.findType = FindOptions::FindReplace;
        opt.searchPattern = ui->cmb1SearchPattern->lineEdit()->text();
        opt.replacePattern = ui->cmb1ReplacePattern->lineEdit()->text();
        break;

    case FindInFilesIdx:
        opt.findType = FindOptions::FindInFiles;
        opt.searchPattern = ui->cmb2SearchPattern->lineEdit()->text();
        opt.replacePattern = ui->cmb2ReplacePattern->lineEdit()->text();
        opt.filters = ui->cmb2Filters->lineEdit()->text();
        opt.directory = ui->cmb2Directory->lineEdit()->text();
        break;
    }

    opt.isCaseSensitive = mGenSettings->isFindCaseSensitiveSet();
    opt.isWholeWords = mGenSettings->isFindWholeWordsSet();
    opt.isRegexp = mGenSettings->isFindRegexpSet();
    opt.isReverseDirection = mGenSettings->isFindReverseDirectionSet();
    opt.isWrap = mGenSettings->isFindWrapSet();
    opt.isInSelection = mGenSettings->isFindInSelectionSet();
    opt.isBookmarkLine = mGenSettings->isFindMarkSet();
    opt.isInSubDirs = mGenSettings->isFindInSubDirsSet();
    opt.isInHiddenDirs = mGenSettings->isFindInHiddenDirsSet();

    return opt;
}


void FindReqWidget::setInitialSearchPattern(const QString &pattern)
{
    int idx = currentIndex();
    switch(idx) {
    case FindIdx:
        ui->cmb0SearchPattern->lineEdit()->setText(pattern);
        break;
    case ReplaceIdx:
        ui->cmb1SearchPattern->lineEdit()->setText(pattern);
        break;
    case FindInFilesIdx:
        ui->cmb2SearchPattern->lineEdit()->setText(pattern);
        break;
    default:
        LOG_ERROR("Wrong FindReqWidget index - %d", idx);
        break;
    }
}

void FindReqWidget::setInitialReplacePattern(const QString &pattern)
{
    int idx = currentIndex();
    switch(idx) {
    case ReplaceIdx:
        ui->cmb1ReplacePattern->lineEdit()->setText(pattern);
        break;
    case FindInFilesIdx:
        ui->cmb2ReplacePattern->lineEdit()->setText(pattern);
        break;
    default:
        LOG_ERROR("Wrong FindReqWidget index - %d", idx);
        break;
    }
}

void FindReqWidget::setInitialFilters(const QString &filters)
{
    int idx = currentIndex();
    if(idx == FindInFilesIdx)
        ui->cmb2Filters->lineEdit()->setText(filters);
    else
        LOG_ERROR("Wrong FindReqWidget index - %d", idx);
}

void FindReqWidget::setInitialDirectory(const QString &directory)
{
    int idx = currentIndex();
    if(idx == FindInFilesIdx)
        ui->cmb2Directory->lineEdit()->setText(directory);
    else
        LOG_ERROR("Wrong FindReqWidget index - %d", idx);
}


void FindReqWidget::onCurrentChanged(int idx)
{
    switch(idx) {
    case FindIdx:
        setupFindWidget();
        break;

    case ReplaceIdx:
        setupReplaceWidget();
        break;

    case FindInFilesIdx:
        setupFindInFilesWidget();
        break;

    default:
        LOG_ERROR("Wrong FindReqWidget index - %d", idx);
        break;
    }
}


void FindReqWidget::setupFindWidget()
{
    ui->btn0CaseSensitive->setChecked(mGenSettings->isFindCaseSensitiveSet());
    ui->btn0Words->setChecked(mGenSettings->isFindWholeWordsSet());
    ui->btn0Regexp->setChecked(mGenSettings->isFindRegexpSet());
    ui->btn0Reverse->setChecked(mGenSettings->isFindReverseDirectionSet());
    ui->btn0Wrap->setChecked(mGenSettings->isFindWrapSet());
    ui->btn0InSelection->setChecked(mGenSettings->isFindInSelectionSet());
    ui->btn0Mark->setChecked(mGenSettings->isFindMarkSet());
}

void FindReqWidget::setupReplaceWidget()
{
    ui->btn1CaseSensitive->setChecked(mGenSettings->isFindCaseSensitiveSet());
    ui->btn1Words->setChecked(mGenSettings->isFindWholeWordsSet());
    ui->btn1Regexp->setChecked(mGenSettings->isFindRegexpSet());
    ui->btn1Reverse->setChecked(mGenSettings->isFindReverseDirectionSet());
    ui->btn1Wrap->setChecked(mGenSettings->isFindWrapSet());
    ui->btn1InSelection->setChecked(mGenSettings->isFindInSelectionSet());
}

void FindReqWidget::setupFindInFilesWidget()
{
    ui->btn2CaseSensitive->setChecked(mGenSettings->isFindCaseSensitiveSet());
    ui->btn2Words->setChecked(mGenSettings->isFindWholeWordsSet());
    ui->btn2Regexp->setChecked(mGenSettings->isFindRegexpSet());
    ui->btn2InSubDirs->setChecked(mGenSettings->isFindInSubDirsSet());
    ui->btn2InHiddenDirs->setChecked(mGenSettings->isFindInHiddenDirsSet());
}
