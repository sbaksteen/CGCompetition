#ifndef CYLINDER_H_
#define CYLINDER_H

#include "../object.h"

class Cylinder: public Object
{
    public:
        Cylinder(double radius, double height);

        virtual Hit intersect(Ray const &ray);
        
        virtual BBox boundingBox() const;

		double r;
		double h;
};

#endif
