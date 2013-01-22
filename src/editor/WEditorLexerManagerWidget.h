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
 *  @file       WEditorLexerManagerWidget.h
 *  @brief      Wolverine::EditorLexerManagerWidget class interface.
 */





#ifndef __W_EDITOR_LEXER_MANAGER_WIDGET_H_
 #define __W_EDITOR_LEXER_MANAGER_WIDGET_H_


#include <QWidget>
#include <QMap>

class QScrollArea;
class QGridLayout;

namespace Ui {
class EditorLexerManagerWidget;
}


namespace Wolverine
{

class EditorLexerCfg;

class EditorLexerManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditorLexerManagerWidget(QMap<QString, EditorLexerCfg*> *lexerMap, QWidget *parent = 0);
    ~EditorLexerManagerWidget();
    
private slots:
    void onLexerChanged(const QString &name);
    void onLexerFontChanged(const QFont &font);
    void onLexerFgColorChanged(const QColor &color);
    void onLexerBgColorChanged(const QColor &color);
    void onLexerFillEoLChanged(bool checked);
    void onShowInMenuChanged(bool checked);

private:
    QWidget* getLexerStyles(const QString &name, EditorLexerCfg *eLexer);
    void setupLexerStyles(const QString &name, EditorLexerCfg *eLexer);

    Ui::EditorLexerManagerWidget *ui;

    QMap<QString, EditorLexerCfg*> *mLexerMap;
    QScrollArea *mScrollArea;
};

}


#endif //__W_EDITOR_LEXER_MANAGER_WIDGET_H_
