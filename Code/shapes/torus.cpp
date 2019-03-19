#include "torus.h"

#include <cmath>

#include <iostream>
#include <algorithm>

#include "polyroots.h"

using namespace std;


std::vector<Interval> Torus::intervals(Ray const &ray) {
	std::vector<Interval> is;
	std::vector<double> ts = intersects(ray);
	std::sort(ts.begin(), ts.end());
	std::vector<Hit> hits;
	for (int i = 0; i < ts.size(); i++) {
		Vector point = ray.at(ts[i]);
		double p2 = sqrt(point.x*point.x + point.z*point.z);
		Point tubeMiddle = Point(point.x*maj/p2, 0, point.z * maj/p2);
		Vector N = point - tubeMiddle;
		hits.push_back(Hit(ts[i], N.normalized(), Point(0,0), &material));
	}
	for (int i = 0; i < hits.size(); i += 2) {
		is.push_back(Interval(hits[i], hits[i+1]));
	}
	return is;
}

std::vector<double> Torus::intersects(Ray const &ray) {
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

	std::vector<double> r = solveQuartic(a, b, c, d, e);
	std::sort(r.begin(), r.end());
	return r;
}

Torus::Torus(double major, double minor)
:
    maj(major),
	min(minor)
{}