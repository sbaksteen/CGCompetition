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
	for (int xi = 0; xi != 2; xi++) {
		for (int yi = 0; yi != 2; yi++) {
			for (int zi = 0; zi != 2; zi++) {
				Point p = Point(xi ? b.vmax.x : b.vmin.x, yi ? b.vmax.y : b.vmin.y, zi ? b.vmax.z : b.vmin.z);
				p = transformMat * p;
				vmin = Point(fmin(vmin.x, p.x), fmin(vmin.y, p.y), fmin(vmin.z, p.z));
				vmax = Point(fmax(vmax.x, p.x), fmax(vmax.y, p.y), fmax(vmax.z, p.z));
			}
		}
	}
	return BBox(vmin, vmax);
}