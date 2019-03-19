#ifndef TORUS_H_
#define TORUS_H_

#include "../object.h"
#include "closedObject.h"
#include <vector>
#include <algorithm>

class Torus: public ClosedObject
{
    public:
        Torus(double major, double minor);

        virtual std::vector<Interval> intervals (Ray const &ray);
        
        std::vector<double> intersects(Ray const &ray);

        double const maj; // major radius
		double const min; // minor radius
};

#endif
