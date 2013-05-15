#ifndef WFINDREQUEST_H
#define WFINDREQUEST_H


#include "WFindHit.h"
#include "WFindOptions.h"

#include <QList>
#include <QMap>


namespace Wolverine {


typedef QList<FindHit> FindHitList;

class FindRequest
{
public:
    FindRequest() :
        isValid(false) { }

    FindRequest(const FindOptions &options) :
        isValid(false), options(options) { }

    bool isValid;
    FindOptions options;
    QMap<QString, FindHitList> hitFiles;
};


};


#endif // WFINDREQUEST_H
