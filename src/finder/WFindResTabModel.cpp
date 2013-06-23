#include "WFindResTabModel.h"


#include <QStringList>
#include <QRegExp>
#include <QDebug>


using namespace Wolverine;

FindResTabModel::FindResTabModel(QObject *parent) :
    QAbstractItemModel(parent),
    mHits(0)
{

}

QModelIndex FindResTabModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid()) {
        if(row >= mHitList.length())
            return QModelIndex();
        else {
            HitFile *hf = mHitList.at(row);
            return createIndex(row, column, hf);

        }
    } else {
        HitFile *hf = static_cast<HitFile*>(parent.internalPointer());
        if(row >= hf->hits.length())
            return QModelIndex();
        else {
            Hit *h = hf->hits.at(row);
            return createIndex(row, column, h);
        }

    }
}

QModelIndex FindResTabModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    Item *item = static_cast<Item*>(child.internalPointer());
    Item *parentItem = item->parrent;

    if(parentItem == 0)
        return QModelIndex();

    HitFile *hf = static_cast<HitFile*>(parentItem);

    int i = mHitList.indexOf(hf);
    return createIndex(i, 0, parentItem);
}

int FindResTabModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
        return 0;

    if(parent.isValid()) {
        Item *item = static_cast<Item*>(parent.internalPointer());
        Item *parentItem = item->parrent;
        if(parentItem == 0) {
            HitFile *hf = static_cast<HitFile*>(parent.internalPointer());
            return hf->hits.length();
        }
        return 0;
    }
    else
        return mHitList.length();
}

int FindResTabModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant FindResTabModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    Item *item = static_cast<Item*>(index.internalPointer());

    if(item->parrent == 0) {
        if(index.column() == 0)
            return mHitList.at(index.row())->filePath;
        return QVariant();
    }

    HitFile *hf = static_cast<HitFile*>(item->parrent);

    if(index.column() == 0)
        return QString::number(hf->hits.at(index.row())->lineNr);
    return hf->hits.at(index.row())->lineText;
}

QVariant FindResTabModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        if (section == 0)
            return QString("Line");
        else
            return QString("Text");
    return QVariant();
}


void FindResTabModel::addHits(const QStringList &list)
{
    this->beginResetModel();
    foreach(QString line, list) {
        mHits++;
        parseLine(line);
    }
    this->endResetModel();
}

int FindResTabModel::getHits()
{
   return mHits;
}

int FindResTabModel::getFiles()
{
    return mHitList.length();
}


void FindResTabModel::showHits()
{
    foreach(HitFile *hf, mHitList) {
        qDebug() << hf->filePath;
        foreach(Hit *h, hf->hits) {
            qDebug() << "\t" << h->lineNr << "\t" << h->lineText;
        }
    }
}


void FindResTabModel::parseLine(const QString &line)
{
    int sep0 = line.indexOf(":", 2); //Start from second due to windows path.
    int sep1 = line.indexOf(":", sep0+1);

    if(sep0 == -1 && sep1 == -1)
        return;

    QString file = line.left(sep0);
    int linenr = line.mid(sep0+1, sep1-sep0-1).toInt();
    QString txt = line.mid(sep1+1);

    for(int i=0; i<mHitList.length(); i++){
        if(mHitList[i]->filePath == file) {
            mHitList[i]->hits.append(new Hit(linenr, txt, mHitList[i]));
            return;
        }
    }

    HitFile *tmp = new HitFile(file);
    tmp->hits.append(new Hit(linenr, txt, tmp));
    mHitList.append(tmp);
}
