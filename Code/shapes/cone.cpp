#include "cone.h"
#include "polyroots.h"
#include <vector>

#include <cmath>

using namespace std;

Hit Cone::intersect(Ray const &ray)
{
	double dx = (ray.D).x;
	double dy = (ray.D).y;
	double dz = (ray.D).z;
	double ox = (ray.O).x;
	double oy = (ray.O).y;
	double oz = (ray.O).z;
	
	double a = dx*dx - dy*dy + dz*dz;
	double b = (dx*ox - dy*oy + dz*oz)*2;
	double c = ox*ox - oy*oy + oz*oz;
	
	vector<double> solutions = solveQuadratic(a, b, c);
	vector<double> validSolutions;
	for (int i = 0; i < solutions.size(); i++) {
		double n = solutions[i];
		Point p = ray.at(n);
		if (p.y <= 0 && p.y >= -h) {
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
	
	N.y = sqrt(N.dot(N));
	
    return Hit(solution, N.normalized());
}

Cone::Cone(double height)
: h(height)
{}
