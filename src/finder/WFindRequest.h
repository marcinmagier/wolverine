#ifndef WFINDREQUEST_H
#define WFINDREQUEST_H


#include "WFindHit.h"
#include "WFindOptions.h"

#include <QList>


namespace Wolverine {


class FindRequest
{
public:
    FindRequest() :
        isValid(false) { }

    FindRequest(const FindOptions &options) :
        isValid(false), options(options) { }

    bool isValid;
    FindOptions options;
    QList<FindHit> hitList;
};


};


#endif // WFINDREQUEST_H
