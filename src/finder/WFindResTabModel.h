#ifndef WFINDRESMODEL_H
#define WFINDRESMODEL_H

#include <QAbstractItemModel>

#include <QStringList>

namespace Wolverine
{

class Item
{
public:
    Item(Item *parrent):
        parrent(parrent) {}

    Item* parrent;
};


class Hit : public Item
{
public:
    Hit(int line, const QString &text, Item *parrent) :
        Item(parrent),
        lineNr(line), lineText(text) {}

    int lineNr;
    QString lineText;
};


class HitFile : public Item
{
public:
    HitFile(const QString &file) :
        Item(0),
        filePath(file) {}

    QString filePath;
    QList<Hit*> hits;
};



class FindResTabModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit FindResTabModel(QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void addHits(const QStringList &list);
    int getHits();
    int getFiles();

    void showHits();
    
signals:
    
public slots:

private:
    void parseLine(const QString &line);

    int mHits;
    QList<HitFile*> mHitList;
    QStringList mList;
    
};


}

#endif // WFINDRESMODEL_H
