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

#include "CfgAppSettings.h"
#include "CfgGeneralSettings.h"


using namespace Wolverine;


/**
 *  Constructor
 *
 * @param parent
 */
FindReqWidget::FindReqWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::FindReqWidget)
{
    mGenSettings = AppSettings::instance()->general;

    ui->setupUi(this);

    ui->btn0CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn0CaseSensitive->setToolTip(tr("Case Sensitive"));
    ui->btn0CaseSensitive->setChecked(mGenSettings->isFindCaseSensitiveSet());
    connect(ui->btn0CaseSensitive, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindCaseSensitive(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findCaseSensitiveChanged(bool)),
            ui->btn0CaseSensitive, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn1CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn1CaseSensitive->setToolTip(tr("Case Sensitive"));
    ui->btn1CaseSensitive->setChecked(mGenSettings->isFindCaseSensitiveSet());
    connect(ui->btn1CaseSensitive, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindCaseSensitive(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findCaseSensitiveChanged(bool)),
            ui->btn1CaseSensitive, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn2CaseSensitive->setIcon(QIcon(":/search_sensitive.png"));
    ui->btn2CaseSensitive->setToolTip(tr("Case Sensitive"));
    ui->btn2CaseSensitive->setChecked(mGenSettings->isFindCaseSensitiveSet());
    connect(ui->btn2CaseSensitive, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindCaseSensitive(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findCaseSensitiveChanged(bool)),
            ui->btn2CaseSensitive, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn0Words->setIcon(QIcon(":/search_words.png"));
    ui->btn0Words->setToolTip(tr("Whole Words"));
    ui->btn0Words->setChecked(mGenSettings->isFindWholeWordsSet());
    connect(ui->btn0Words, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWholeWords(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findWholeWordsChanged(bool)),
            ui->btn0Words, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn1Words->setIcon(QIcon(":/search_words.png"));
    ui->btn1Words->setToolTip(tr("Whole Words"));
    ui->btn1Words->setChecked(mGenSettings->isFindWholeWordsSet());
    connect(ui->btn1Words, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWholeWords(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findWholeWordsChanged(bool)),
            ui->btn1Words, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn2Words->setIcon(QIcon(":/search_words.png"));
    ui->btn2Words->setToolTip(tr("Whole Words"));
    ui->btn2Words->setChecked(mGenSettings->isFindWholeWordsSet());
    connect(ui->btn2Words, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWholeWords(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findWholeWordsChanged(bool)),
            ui->btn2Words, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn0Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn0Regexp->setToolTip(tr("Regular Expression"));
    ui->btn0Regexp->setChecked(mGenSettings->isFindRegexpSet());
    connect(ui->btn0Regexp, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindRegexp(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findRegexpChanged(bool)),
            ui->btn0Regexp, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn1Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn1Regexp->setToolTip(tr("Regular Expression"));
    ui->btn1Regexp->setChecked(mGenSettings->isFindRegexpSet());
    connect(ui->btn1Regexp, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindRegexp(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findRegexpChanged(bool)),
            ui->btn1Regexp, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn2Regexp->setIcon(QIcon(":/search_regexp.png"));
    ui->btn2Regexp->setToolTip(tr("Regular Expression"));
    ui->btn2Regexp->setChecked(mGenSettings->isFindRegexpSet());
    connect(ui->btn2Regexp, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindRegexp(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findRegexpChanged(bool)),
            ui->btn2Regexp, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn0Reverse->setIcon(QIcon(":/search_reverse.png"));
    ui->btn0Reverse->setToolTip(tr("Reverse Direction"));
    ui->btn0Reverse->setChecked(mGenSettings->isFindReverseDirectionSet());
    connect(ui->btn0Reverse, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindReverseDirection(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findReverseDirectionChanged(bool)),
            ui->btn0Reverse, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn1Reverse->setIcon(QIcon(":/search_reverse.png"));
    ui->btn1Reverse->setToolTip(tr("Reverse Direction"));
    ui->btn1Reverse->setChecked(mGenSettings->isFindReverseDirectionSet());
    connect(ui->btn1Reverse, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindReverseDirection(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findReverseDirectionChanged(bool)),
            ui->btn1Reverse, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn0Wrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btn0Wrap->setToolTip(tr("Wrap"));
    ui->btn0Wrap->setChecked(mGenSettings->isFindWrapSet());
    connect(ui->btn0Wrap, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWrap(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findWrapChanged(bool)),
            ui->btn0Wrap, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn1Wrap->setIcon(QIcon(":/search_wrap.png"));
    ui->btn1Wrap->setToolTip(tr("Wrap"));
    ui->btn1Wrap->setChecked(mGenSettings->isFindWrapSet());
    connect(ui->btn1Wrap, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindWrap(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findWrapChanged(bool)),
            ui->btn1Wrap, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn0InSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btn0InSelection->setToolTip(tr("In Selection"));
    ui->btn0InSelection->setChecked(mGenSettings->isFindInSelectionSet());
    connect(ui->btn0InSelection, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInSelection(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findInSelectionChanged(bool)),
            ui->btn0InSelection, SLOT(setChecked(bool)), Qt::DirectConnection);

    ui->btn1InSelection->setIcon(QIcon(":/search_selection.png"));
    ui->btn1InSelection->setToolTip(tr("In Selection"));
    ui->btn1InSelection->setChecked(mGenSettings->isFindInSelectionSet());
    connect(ui->btn1InSelection, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInSelection(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findInSelectionChanged(bool)),
            ui->btn1InSelection, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn0Mark->setIcon(QIcon(":/search_mark.png"));
    ui->btn0Mark->setToolTip("Bookmark Line");
    ui->btn0Mark->setChecked(mGenSettings->isFindMarkSet());
    connect(ui->btn0Mark, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindMark(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findMarkChanged(bool)),
            ui->btn0Mark, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn2InSubDirs->setIcon(QIcon(":/search_subdirs.png"));
    ui->btn2InSubDirs->setToolTip(tr("Search in sub-folders"));
    ui->btn2InSubDirs->setChecked(mGenSettings->isFindInSubDirsSet());
    connect(ui->btn2InSubDirs, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInSubDirs(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findInSubDirsChanged(bool)),
            ui->btn2InSubDirs, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn2InHiddenDirs->setIcon(QIcon(":/search_hidden.png"));
    ui->btn2InHiddenDirs->setToolTip(tr("Search in hidden folders"));
    ui->btn2InHiddenDirs->setChecked(mGenSettings->isFindInHiddenDirsSet());
    connect(ui->btn2InHiddenDirs, SIGNAL(toggled(bool)),
            mGenSettings, SLOT(setFindInHiddenDirs(bool)), Qt::DirectConnection);
    connect(mGenSettings, SIGNAL(findInHiddenDirsChanged(bool)),
            ui->btn2InHiddenDirs, SLOT(setChecked(bool)), Qt::DirectConnection);


    ui->btn2SelectDir->setIcon(QIcon(":/search_select_dir.png"));
    ui->btn2SelectDir->setToolTip(tr("Select Directory"));

    ui->btn2CurrentDir->setIcon(QIcon(":/search_current_dir.png"));
    ui->btn2CurrentDir->setToolTip(tr("Select Current Document's Directory"));

}


/**
 *  Destructor
 */
FindReqWidget::~FindReqWidget()
{
    delete ui;
}
