#include "plane.h"

#include <cmath>

#include <iostream>

using namespace std;

Hit Plane::intersect(Ray const &ray)
{

	double denom = N.dot(ray.D);
	
	if (denom == 0){
		return Hit::NO_HIT();
	}
    double solution = (N.dot(-ray.O) / N.dot(ray.D));
    
    if (solution < 0){
		return Hit::NO_HIT();
	}
    
	if (N.dot(ray.D) > 0){
		return Hit(solution, -N);
	}
	
	return Hit(solution, N);

}

Plane::Plane(Vector N)
:
    N(N.normalized())
{}
