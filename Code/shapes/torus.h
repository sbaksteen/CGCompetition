#ifndef TORUS_H_
#define TORUS_H_

#include "../object.h"

class Torus: public Object
{
    public:
        Torus(double major, double minor);

        virtual Hit intersect(Ray const &ray);

        double const maj; // major radius
		double const min; // minor radius
};

#endif
