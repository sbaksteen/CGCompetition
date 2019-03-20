#include "quad.h"

#include <cmath>

#include <iostream>

#include <limits>

using namespace std;

Hit Quad::intersect(Ray const &ray) 
{
	Hit solution1 = t1->intersect(ray);
	Hit solution2 = t2->intersect(ray);
	 
	if (solution1.t < numeric_limits<double>::infinity()){
		return Hit(solution1.t, solution1.N);
	}
	if (solution2.t < numeric_limits<double>::infinity()){
		return Hit(solution2.t, solution2.N);
	}
	
	return Hit::NO_HIT();
	
}

BBox Quad::boundingBox() const {
    BBox b1 = t1->boundingBox(),
         b2 = t2->boundingBox();

    return BBox(
        Point(fmin(b1.vmin.x, b2.vmin.x), fmin(b1.vmin.y, b2.vmin.y), fmin(b1.vmin.z, b2.vmin.z)),
        Point(fmax(b1.vmax.x, b2.vmax.x), fmax(b1.vmax.y, b2.vmax.y), fmax(b1.vmax.z, b2.vmax.z))
    );
}

Quad::Quad(Vertex a, Vertex b, Vertex c, Vertex d){
	t1 = new Triangle(a,b,c, ShadingType::Flat);
	t2 = new Triangle(a,c,d, ShadingType::Flat);
}
