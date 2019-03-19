#include "sphere.h"

#include <cmath>

#include <iostream>

#include "polyroots.h"

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    *
    * Insert calculation of ray/sphere intersection here.
    *
    * You have the sphere's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    // place holder for actual intersection calculation

	double solution = minPos(intersects(ray));
	if (solution < 0) {
		return Hit::NO_HIT();
	}
	
	/****************************************************
	* RT1.2: NORMAL CALCULATION
	*
	* Given: t, C, r
	* Sought: N
	*
	* Insert calculation of the sphere's normal at the intersection point.
	****************************************************/
	Vector point = ray.at(solution);
	Vector N = point;

	Point tex = textureCoordAt(point);

	return Hit(solution,N.normalized(), tex);

}

std::vector<double> Sphere::intersects(Ray const &ray) {
	double a = (ray.D).dot(ray.D);
    double b = 2*(ray.D).dot(ray.O);
    double c = (ray.O).dot(ray.O) - r*r;
	return solveQuadratic(a, b, c);
}

Point Sphere::textureCoordAt(Point const &p) {
	double theta = acos(p.z/r);
	double phi = atan2(p.y, p.x);
	if (phi < 0) {
		phi += 2*M_PI;
	}
	double u = 1 - phi/(2*M_PI);
	double v = (M_PI-theta)/M_PI;
	return Point(u, v, 0);
}

Sphere::Sphere(double radius)
:
    r(radius)
{}
