#include "torus.h"

#include <cmath>

#include <iostream>

#include "polyroots.h"

using namespace std;

Hit Torus::intersect(Ray const &ray) {
	double dir2 = (ray.D).dot(ray.D);
	double o2 = (ray.O).dot(ray.O);
	double diro = (ray.D).dot(ray.O);
	double min2 = min*min;
	double maj2 = maj*maj;
	double o2adj = o2 - (min2 + maj2);
	
	double dy = (ray.D).y;
	double oy = (ray.O).y;
	
	double a = dir2*dir2;
	double b = 4*dir2*diro;
	double c = 2*dir2*o2adj + 4*diro*diro + 4*maj2*dy*dy;
	double d = 4*o2adj*diro + 8*maj2*oy*dy;
	double e = o2adj*o2adj - 4*maj2*(min2 - oy*oy);
	
	double solution = minPos(solveQuartic(a, b, c, d, e));
	if (solution < 0) {
		return Hit::NO_HIT();
	}
	
	// calculate normal
	Vector point = ray.at(solution);
	double p2 = sqrt(point.x*point.x + point.z*point.z);
	Point tubeMiddle = Point(point.x*maj/p2, 0, point.z * maj/p2);
	Vector N = point - tubeMiddle;
	return Hit(solution, N.normalized());
}

Torus::Torus(double major, double minor)
:
    maj(major),
	min(minor)
{}