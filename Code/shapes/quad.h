#ifndef QUAD_H_
#define QUAD_H_

#include "../object.h"
#include "../vertex.h"
#include "triangle.h"


class Quad: public Object
{
    public:
        Quad(Vertex a, Vertex b, Vertex c, Vertex d);

        virtual Hit intersect(Ray const &ray);
        
		Triangle* t1;
		Triangle* t2;
};

#endif
