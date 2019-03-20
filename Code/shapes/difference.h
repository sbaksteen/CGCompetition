#ifndef DIFFERENCE_H_
#define DIFFERENCE_H_

#include "closedObject.h"
#include "../object.h"

class Difference : public ClosedObject {
    public:
        Difference(ClosedPtr o1, ClosedPtr o2) : o1(o1), o2(o2) {}

        virtual vector<Interval> intervals(Ray const &ray);
        
        virtual BBox boundingBox() const;

        ClosedPtr o1, o2;
};

#endif
