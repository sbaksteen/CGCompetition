#include "intersection.h"

vector<Interval> Intersection::intervals(Ray const &ray) {
    vector<Interval> result;
    vector<Interval> v1 = o1->intervals(ray);
    vector<Interval> v2 = o2->intervals(ray);
    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v2.size(); j++) {
            vector<Interval> ir = v1[i] * v2[j];
            for (int k = 0; k < ir.size(); k++) {
                smartAdd(result, ir[k]);
            }
        }
    }
    return result;
}

BBox Intersection::boundingBox() const {
    BBox b1 = o1->boundingBox(),
         b2 = o2->boundingBox();

    return BBox(
        Point(fmax(b1.vmin.x, b2.vmin.x), fmax(b1.vmin.y, b2.vmin.y), fmax(b1.vmin.z, b2.vmin.z)),
        Point(fmin(b1.vmax.x, b2.vmax.x), fmin(b1.vmax.y, b2.vmax.y), fmin(b1.vmax.z, b2.vmax.z))
    );
}