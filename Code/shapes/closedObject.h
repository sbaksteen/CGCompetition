#ifndef CLOSED_OBJECT_H_
#define CLOSED_OBJECT_H_

#include "../object.h"
#include <vector>

class ClosedObject : public Object {
    public:
        virtual std::vector<double> intersects(Ray const &ray) = 0;

        virtual Hit intersect(Ray const &ray) = 0; 
};

#endif