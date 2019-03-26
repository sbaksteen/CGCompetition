#ifndef RAY_INFINITECYLINDER_H
#define RAY_INFINITECYLINDER_H


#include "closedObject.h"

class InfiniteCylinder : public ClosedObject {
public:
    virtual std::vector<Interval> intervals(Ray const &ray);
    double r;

    InfiniteCylinder(double r) : r(r) {}
};


#endif //RAY_INFINITECYLINDER_H
