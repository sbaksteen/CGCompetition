#include "box.h"
#include <cmath>
#include <iostream>

using namespace std;

vector<Interval> Box::intervals(Ray const &ray) {
    Vector N1;
    Vector N2;
    Point tx1;
    Point tx2;
    Vector tmin = (vmin - ray.O) / ray.D;
    Vector tmax = (vmax - ray.O) / ray.D;
    
    if (tmin.x > tmax.x) {
        double temp = tmin.x;
        tmin.x = tmax.x;
        tmax.x = temp;
    }
    if (tmin.y > tmax.y) {
        double temp = tmin.y;
        tmin.y = tmax.y;
        tmax.y = temp;
    }
    if (tmin.z > tmax.z) {
        double temp = tmin.z;
        tmin.z = tmax.z;
        tmax.z = temp;
    }

    double low, hi;

    if (tmin.x > tmin.y && tmin.x > tmin.z) {
        N1 = Vector(1, 0, 0);
        low = tmin.x;
        Point p = ray.at(low);
        tx1 = Point((p.z - vmin.z) / (vmax.z - vmin.z), (p.y - vmin.y) / (vmax.y - vmin.y));
    }
    else if (tmin.y > tmin.z) {
        N1 = Vector(0, 1, 0);
        low = tmin.y;
        Point p = ray.at(low);
        tx1 = Point((p.x - vmin.x) / (vmax.x - vmin.x), (p.z - vmin.z) / (vmax.z - vmin.z));
    }
    else {
        N1 = Vector(0, 0, 1);
        low = tmin.z;
        Point p = ray.at(low);
        tx1 = Point((p.x - vmin.x) / (vmax.x - vmin.x), (p.y - vmin.y) / (vmax.y - vmin.y));
    }

    if (tmax.x < tmax.y && tmax.x < tmax.z) {
        N2 = Vector(1, 0, 0);
        hi = tmax.x;
        Point p = ray.at(hi);
        tx2 = Point((p.z - vmin.z) / (vmax.z - vmin.z), p.y - vmin.y / (vmax.y - vmin.y));
    }
    else if (tmax.y < tmax.z) {
        N2 = Vector(0, 1, 0);
        hi = tmax.y;
        Point p = ray.at(hi);
        tx2 = Point((p.x - vmin.x) / (vmax.x - vmin.x), (p.z - vmin.z) / (vmax.z - vmin.z));
    }
    else {
        N2 = Vector(0, 0, 1);
        hi = tmax.z;
        Point p = ray.at(hi);
        tx2 = Point((p.x - vmin.x) / (vmax.x - vmin.x), (p.y - vmin.y) / (vmax.y - vmin.y));
    }


    if (low > hi) {
        return vector<Interval>();
    }
    vector<Interval> v;

    v.push_back(Interval(Hit(low, N1, tx1, &material), Hit(hi, N2, tx2, &material)));
    return v;
}

BBox Box::boundingBox() const {
    return BBox(vmin, vmax);
}