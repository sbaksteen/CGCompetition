#ifndef UNION_H_
#define UNION_H_

#include "closedObject.h"
#include "../object.h"

class Union : public ClosedObject {
    public:
        Union(ObjectPtr o1, ObjectPtr o2) : o1(o1), o2(o2) {}

        virtual Hit intersect(Ray const &ray);

        virtual vector<double> intersects(Ray const &ray);

        ObjectPtr o1, o2;
};

#endif
