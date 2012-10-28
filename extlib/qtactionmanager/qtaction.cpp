
#include "qtaction.h"

#include <QObject>
#include <QAction>


QtAction::QtAction(QAction *action)
{
    this->action = action;
    this->schemeBinding["Default"] = action->shortcut().toString();
}

QtAction::QtAction(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
}

QtAction& QtAction::operator =(const QtAction &other)
{
    this->action = other.action;
    this->schemeBinding = other.schemeBinding;
    return *this;
}

QString QtAction::shortcut(QString scheme)
{
    return this->schemeBinding[scheme];
}

