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

Quad::Quad(Vertex a, Vertex b, Vertex c, Vertex d){
	t1 = new Triangle(a,b,c, ShadingType::Flat);
	t2 = new Triangle(a,c,d, ShadingType::Flat);
}
