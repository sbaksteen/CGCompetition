#include "closedTransformedObject.h"

std::vector<Interval> ClosedTransformedObject::intervals(Ray const &ray) {
	Ray newRay = Ray(transformInv * ray.O, transformInv.noTranslation() * ray.D);
    std::vector<Interval> is = o->intervals(newRay);
    for (int i = 0; i < is.size(); i++) {
        is[i].in.N = (transformInv.transposed() * is[i].in.N).normalized();
        is[i].out.N = (transformInv.transposed() * is[i].out.N).normalized();
    }
    return is;
}