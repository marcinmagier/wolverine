#include "WFindResTabModel.h"


#include <QStringList>
#include <QDebug>


using namespace Wolverine;

FindResTabModel::FindResTabModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

QModelIndex FindResTabModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex FindResTabModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int FindResTabModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int FindResTabModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant FindResTabModel::data(const QModelIndex &index, int role) const
{
    return 0;
}


void FindResTabModel::addHits(const QStringList &list)
{
    mList.append(list);
}

int FindResTabModel::getHits()
{
   return mList.count();
}

int FindResTabModel::getFiles()
{
    return mList.count();
}


void FindResTabModel::showHits()
{
    foreach(QString str, mList) {
        qDebug() << str;
    }
}
