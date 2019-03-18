#include "mesh.h"

#include <cmath>

#include <iostream>

#include <limits>

using namespace std;

Hit Mesh::intersect(Ray const &ray) 
{
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    for (unsigned idx = 0; idx != triangles.size(); ++idx)
    {
        Hit hit(triangles[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
        }
    }
    
    return min_hit;
}

Mesh::Mesh(vector<Vertex> verts, ShadingType s) {
	for(unsigned i = 0; i < verts.size(); i += 3){
		triangles.push_back(new Triangle(verts[i], verts[i+1], verts[i+2], s));
	}
}
