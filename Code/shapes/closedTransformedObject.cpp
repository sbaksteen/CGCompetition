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

BBox ClosedTransformedObject::boundingBox() const {
	BBox b = o->boundingBox();
	if (isnan(b.vmin.x)) return BBox::NO_BOX();
	Point tmin = transformMat * b.vmin;
	Point tmax = transformMat * b.vmax;
	Point vmin = Point(fmin(tmin.x, tmax.x), fmin(tmin.y, tmax.y), fmin(tmin.z, tmax.z));
	Point vmax = Point(fmax(tmin.x, tmax.x), fmax(tmin.y, tmax.y), fmax(tmin.z, tmax.z));
	return BBox(vmin, vmax);
}