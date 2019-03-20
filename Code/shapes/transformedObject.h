#ifndef TRANSFORMED_OBJECT_H_
#define TRANSFORMED_OBJECT_H_

#include "../object.h"
#include "../matrix.h"

class TransformedObject: public Object
{
    public:
        TransformedObject(ObjectPtr const &obj, Matrix44 transformMatrix);

        virtual Hit intersect(Ray const &ray);

        virtual BBox boundingBox() const;
		
		    void transform(Matrix44 const &m);

    private:
		ObjectPtr obj;
		Matrix44 transformMat;
		Matrix44 transformInv;
};

#endif
