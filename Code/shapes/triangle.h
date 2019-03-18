#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../object.h"
#include "../vertex.h"

class Triangle: public Object
{
    public:
        Triangle(Vertex a, Vertex b, Vertex c);

        virtual Hit intersect(Ray const &ray);

        Vertex va;
        Vertex vb;
        Vertex vc;
};

#endif
