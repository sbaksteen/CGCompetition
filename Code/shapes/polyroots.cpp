#include "polyroots.h"
#include <cmath>
#include <vector>

using namespace std;

vector<double> solveQuadratic(double a, double b, double c) {
	vector<double> result;
	double discrim = b*b - 4*a*c;
	if (discrim < 0) {
		return result;
	} 
	result.push_back((-b - sqrt(discrim)) / (2*a));
	result.push_back((-b + sqrt(discrim)) / (2*a));
	return result;
}

vector<double> solveCubic(double a, double b, double c, double d) {
	vector<double> roots;
	double a2 = a*a;
	double a3 = a2*a;
	double b2 = b*b;
	double b3 = b2*b;
	double c2 = c*c;
	double c3 = c2*c;
	double d2 = d*d;
	
	double discrim = 18*a*b*c*d - 4*b3*d + b2*c2 - 4*a*c3 - 27*a2*d2;
	// reduce to the depressed cubic: t^3 + pt + q = 0, where x = t - b/3a
	double p = (3*a*c - b2)/(3*a2);
	double q = (2*b3 - 9*a*b*c + 27*a2*d)/(27*a3);
	
	if (discrim < 0) {
		if (p > 0) {
			double r3p = sqrt(p/3);
			double ash = (3*q)/(2*p)*(1/r3p);
			double t0 = -2*r3p*sinh(asinh(ash)/3);
			roots.push_back(t0 - b/(3*a));
			return roots;
		}
		double r3p = sqrt(-p/3);
		double ach = (-3*fabs(q))/(2*p)*(1/r3p);
		double t0 = -2*(fabs(q)/q)*r3p*cosh(acosh(ach)/3);
		roots.push_back(t0 - b/(3*a));
		return roots;
	}
	// discrim >= 0 means three real roots.
	double r3p = sqrt(-p/3);
	double ac = (3*q)/(2*p)*(1/r3p);
	for (int k = 0; k < 3; k++) {
		double tk = 2*r3p*cos(acos(ac)/3 - (2*M_PI*k)/3);
		roots.push_back(tk - b/(3*a));
	}
	return roots;
}

vector<double> solveQuartic(double a, double b, double c, double d, double e) {
	vector<double> roots;
	// simplify to a = 1:
	b /= a;
	c /= a;
	d /= a;
	e /= a;
	
	// reduce to depressed quartic y^4 + py^2 + qy + r = 0, where x = y - b/4.
	double p = (8*c - 3*b*b)/8;
	double q = (b*b*b - 4*b*c + 8*d)/8;
	double r = (-3*b*b*b*b + 256*e - 64*b*d + 16*b*b*c)/256;
	
	// solve the resolvent cubic:
	vector<double> resolv = solveCubic(8, 8*p, 2*p*p - 8*r, -q*q);
	
	// take the real solution
	double m = resolv[0];
	
	if (m < 0) {
		return roots;
	}
	
	double r2m = sqrt(2*m);
	// now there are two quadratics:
	vector<double> q1 = solveQuadratic(1, r2m, p/2 + m - q/(2*r2m));
	vector<double> q2 = solveQuadratic(1, -r2m, p/2 + m + q/(2*r2m));
	for (int i = 0; i < q1.size(); i++) {
		roots.push_back(q1[i] - b/4);
	}
	for (int i = 0; i < q2.size(); i++) {
		roots.push_back(q2[i] - b/4);
	}
	return roots;
}

double minPos(vector<double> v) {
	// returns the minimal positive element in vector v, and -1 if no positive elements exist.
	double min = -1;
	for (int i = 0; i < v.size(); i++) {
		double n = v[i];
		if (n >= 0) {
			if (min < 0 || n < min) {
				min = n;
			}
		}
	}
	return min;
}