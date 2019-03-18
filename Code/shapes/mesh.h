#ifndef MESH_H_
#define MESH_H_

#include "../object.h"
#include "../vertex.h"
#include "triangle.h"

#include <vector>

using namespace std;

class Mesh: public Object
{
    public:
        Mesh(vector<Vertex> verts, ShadingType s);

        virtual Hit intersect(Ray const &ray);
        
		vector<Triangle*> triangles;
};

#endif
