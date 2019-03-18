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


Point TransformedObject::textureCoordAt(Point const &p) {
	return obj->textureCoordAt(transformInv * p);
}