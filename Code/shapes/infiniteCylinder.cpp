#include <algorithm>
#include "infiniteCylinder.h"
#include "polyroots.h"

using namespace std;

std::vector<Interval> InfiniteCylinder::intervals(Ray const &ray) {
    std::vector<Interval> is;
    Point xzo = Point((ray.O).x, 0, (ray.O).z);
    Point xzd = Point((ray.D).x, 0, (ray.D).z);

    double a = xzd.dot(xzd);
    double b = 2*xzo.dot(xzd);
    double c = xzo.dot(xzo) - r*r;
    std::vector<double> ts = solveQuadratic(a, b, c);
    std::sort(ts.begin(), ts.end());
    std::vector<Hit> hits;
    for (int i = 0; i < ts.size(); i++) {
        Vector N = ray.at(ts[i]);
        hits.push_back(Hit(ts[i], N.normalized(), Point(), &material));
    }
    for (int i = 0; i < hits.size(); i += 2) {
        is.push_back(Interval(hits[i], hits[i+1]));
    }
    return is;
}