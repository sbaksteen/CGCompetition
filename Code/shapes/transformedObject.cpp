#include "transformedObject.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit TransformedObject::intersect(Ray const &ray)
{
	Ray newRay = Ray(transformInv * ray.O, transformInv.noTranslation() * ray.D);
	Hit h = obj->intersect(newRay);
	h.N = (transformInv.transposed() * h.N).normalized();
	return h;
}

TransformedObject::TransformedObject(ObjectPtr const &o, Matrix44 transformMatrix) {
	obj = o;
	material = obj->material;
	transformMat = transformMatrix;
	transformInv = transformMat.inverse();
}

void TransformedObject::transform(Matrix44 const &m) {
	transformMat *= m;
	transformInv = transformMat.inverse();
}

BBox TransformedObject::boundingBox() const {
	BBox b = obj->boundingBox();
	if (isnan(b.vmin.x)) return BBox::NO_BOX();
	Point tmin = transformMat * b.vmin;
	Point tmax = transformMat * b.vmax;
	Point vmin = Point(fmin(tmin.x, tmax.x), fmin(tmin.y, tmax.y), fmin(tmin.z, tmax.z));
	Point vmax = Point(fmax(tmin.x, tmax.x), fmax(tmin.y, tmax.y), fmax(tmin.z, tmax.z));
	return BBox(vmin, vmax);
}