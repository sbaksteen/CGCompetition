#ifndef PLANE_H_
#define PLANE_H_

#include "../object.h"

class Plane: public Object
{
    public:
        Plane(Vector N);

        virtual Hit intersect(Ray const &ray);

        Vector const N;
};

#endif
