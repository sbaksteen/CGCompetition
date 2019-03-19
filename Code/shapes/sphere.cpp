#include "sphere.h"

#include <cmath>

#include <iostream>
#include <algorithm>

#include "polyroots.h"

using namespace std;

std::vector<Interval> Sphere::intervals(Ray const &ray) {
	std::vector<Interval> is;
	std::vector<double> ts = intersects(ray);
	std::sort(ts.begin(), ts.end());
	std::vector<Hit> hits;
	for (int i = 0; i < ts.size(); i++) {
		Vector N = ray.at(ts[i]);
		Point tex = textureCoordAt(N);
		hits.push_back(Hit(ts[i], N.normalized(), tex, &material));
	}
	for (int i = 0; i < hits.size(); i += 2) {
		is.push_back(Interval(hits[i], hits[i+1]));
	}
	return is;
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
