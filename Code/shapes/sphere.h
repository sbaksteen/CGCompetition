#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"

class Sphere: public Object
{
    public:
        Sphere(double radius);

        virtual Hit intersect(Ray const &ray);
		
        double const r;
		
    private:
        Point textureCoordAt(Point const &p);
};

#endif
