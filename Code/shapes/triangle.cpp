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

	Vector N;
	if (s == ShadingType::Flat) {
		Point v1(va.x, va.y, va.z);
		Point v2(vb.x, vb.y, vb.z);
		Point v3(vc.x, vc.y, vc.z);
		
		N = ((v2 - v1).cross(v3 - v1)).normalized();
	}
	else if (s == ShadingType::Phong) {
		Vector n1(va.nx, va.ny, va.nz);
		Vector n2(vb.nx, vb.ny, vb.nz);
		Vector n3(vc.nx, vc.ny, vc.nz);

		N = (n3*gamma + n2*beta + n1*(1-gamma-beta)).normalized();
	}

	Point tex = textureCoordAt(beta, gamma);
	
	if (N.dot(ray.D) > 0){
		return Hit(solution, -N, tex);
	}
	
    return Hit(solution, N, tex);
}

Point Triangle::textureCoordAt(float beta, float gamma) {
	return Point(va.u + beta*(vb.u-va.u) + gamma*(vc.u-va.u),
				 1 - (va.v + beta*(vb.v-va.v) + gamma*(vc.v-va.v)));
}

BBox Triangle::boundingBox() const {
	return BBox(
		Point(fmin(va.x, fmin(vb.x, vc.x)), fmin(va.y, fmin(vb.y, vc.y)), fmin(va.z, fmin(vb.z, vc.z))),
		Point(fmax(va.x, fmax(vb.x, vc.x)), fmax(va.y, fmax(vb.y, vc.y)), fmax(va.z, fmax(vb.z, vc.z)))
	);
}

Triangle::Triangle(Vertex a, Vertex b, Vertex c, ShadingType s)
:
	va(a),
	vb(b),
	vc(c),
	s(s)
{}
