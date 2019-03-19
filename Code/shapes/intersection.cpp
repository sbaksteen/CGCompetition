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