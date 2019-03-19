#ifndef UNION_H_
#define UNION_H_

#include "closedObject.h"
#include "../object.h"

class Union : public ClosedObject {
    public:
        Union(ClosedPtr o1, ClosedPtr o2) : o1(o1), o2(o2) {}

        virtual vector<Interval> intervals(Ray const &ray);

        ClosedPtr o1, o2;
};

#endif
