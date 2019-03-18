#include "triangle.h"

#include <cmath>

#include <iostream>

Hit Triangle::intersect(Ray const &ray)
{
	double a = va.x - vb.x;
	double b = va.y - vb.y;
	double c = va.z - vb.z;
	double d = va.x - vc.x;
	double e = va.y - vc.y;
	double f = va.z - vc.z;
	double g = ray.D.x;
	double h = ray.D.y;
	double i = ray.D.z;
	double j = va.x - ray.O.x;
	double k = va.y - ray.O.y;
	double l = va.z - ray.O.z;
	
	double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
	
	double beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	
	double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	
	double solution = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;
	
	if(solution < 0 || gamma < 0 || gamma > 1 || beta < 0 || (beta > 1 - gamma)){
		return Hit::NO_HIT();
	}

    Point v1(va.x, va.y, va.z);
	Point v2(vb.x, vb.y, vb.z);
	Point v3(vc.x, vc.y, vc.z);
	
	Vector N = ((v2 - v1).cross(v3 - v1)).normalized();
	
	if (N.dot(ray.D) > 0){
		return Hit(solution, -N);
	}
	
    return Hit(solution, N);
}

Triangle::Triangle(Vertex a, Vertex b, Vertex c)
:
	va(a),
	vb(b),
	vc(c)
{}
