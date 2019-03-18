#ifndef CONE_H_
#define CONE_H_

#include "../object.h"

class Cone: public Object
{
    public:
        Cone(double height);

        virtual Hit intersect(Ray const &ray);

		double h;
};

#endif
