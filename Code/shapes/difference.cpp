#include "difference.h"

vector<Interval> Difference::intervals(Ray const &ray) {
    vector<Interval> result;
    vector<Interval> v1 = o1->intervals(ray);
    vector<Interval> v2 = o2->intervals(ray);
    if (v2.size() == 0) {
        return v1;
    }
    for (int i = 0; i < v1.size(); i++) {
        vector<Interval> ir;
        ir.push_back(v1[i]);
        for (int j = 0; j < v2.size(); j++) {
            vector<Interval> r;
            for (int k = 0; k < ir.size(); k++) {
                vector<Interval> diff = ir[k] - v2[j];
                for (int l = 0; l < diff.size(); l++) {
                    smartAdd(r, diff[l]);
                }
            }
            ir = r;
        }
        for (int k = 0; k < ir.size(); k++) {
            smartAdd(result, ir[k]);
        }
    }
    return result;
}

BBox Difference::boundingBox() const {
    return o1->boundingBox();
}