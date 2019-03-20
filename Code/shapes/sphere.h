#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"
#include "closedObject.h"
#include <vector>

class Sphere: public ClosedObject
{
    public:
        Sphere(double radius);

        virtual std::vector<Interval> intervals (Ray const &ray);
        
        virtual BBox boundingBox() const;

        std::vector<double> intersects(Ray const &ray);
		
        double const r;
		
    private:
        Point textureCoordAt(Point const &p);
};

#endif
