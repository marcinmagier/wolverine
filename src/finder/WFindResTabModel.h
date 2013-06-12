#ifndef WFINDRESMODEL_H
#define WFINDRESMODEL_H

#include <QAbstractItemModel>

#include <QStringList>

namespace Wolverine
{

class Hit
{
    int lineNr;
    QString lineText;
};

class HitFile
{
    QString file;
    QList<Hit> hits;
};


class FindResTabModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit FindResTabModel(QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void addHits(const QStringList &list);
    int getHits();
    int getFiles();

    void showHits();
    
signals:
    
public slots:

private:
    QList<HitFile> mHitList;
    QStringList mList;
    
};


}

#endif // WFINDRESMODEL_H
