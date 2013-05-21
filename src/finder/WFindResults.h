


#ifndef __W_FIND_RESULTS_H_
 #define __W_FIND_RESULTS_H_


#include "WFindHit.h"
#include "WFindRequest.h"

#include <QList>
#include <QMap>


namespace Wolverine {


typedef QList<FindHit> FindHitList;

class FindResults
{
public:
    FindResults() :
        isValid(false) { }

    FindResults(const FindRequest &options) :
        isValid(false), options(options) { }

    bool isValid;
    FindRequest options;
    QMap<QString, FindHitList> hitFiles;
};


};


#endif // __W_FIND_RESULTS_H_
