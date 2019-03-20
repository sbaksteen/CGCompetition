#ifndef CLOSED_TRANSFORMED_OBJECT_H_
#define CLOSED_TRANSFORMED_OBJECT_H_

#include "transformedObject.h"
#include "closedObject.h"

class ClosedTransformedObject : public ClosedObject {
    public:
        virtual std::vector<Interval> intervals(Ray const &ray);

        ClosedTransformedObject(ClosedPtr o, Matrix44 m) : o(o), transformMat(m) {
            material = o->material;
            transformInv = transformMat.inverse();
        }
        
        virtual BBox boundingBox() const;

        ClosedPtr o;
        Matrix44 transformMat;
        Matrix44 transformInv;

};

#endif