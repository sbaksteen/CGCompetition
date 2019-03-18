#include "cylinder.h"
#include "polyroots.h"

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

Hit Cylinder::intersect(Ray const &ray)
{
	Point xzo = Point((ray.O).x, 0, (ray.O).z);
	Point xzd = Point((ray.D).x, 0, (ray.D).z);
	
	double a = xzd.dot(xzd);
	double b = 2*xzo.dot(xzd);
	double c = xzo.dot(xzo) - r*r;
	
	vector<double> solutions = solveQuadratic(a, b, c);
	vector<double> validSolutions;
	for (int i = 0; i < solutions.size(); i++) {
		double n = solutions[i];
		Point p = ray.at(n);
		if (p.y >= 0 && p.y <= h) {
			validSolutions.push_back(n);
		}
	}
	if (validSolutions.size() == 0) {
		return Hit::NO_HIT();
	}
	double solution = minPos(validSolutions);
	Point i = ray.at(solution);
	Point xzi = Point(i.x, 0, i.z);
	Vector N = xzi;
	
    return Hit(solution, N.normalized());
}

Cylinder::Cylinder(double radius, double height)
: r(radius),
  h(height)
{}
