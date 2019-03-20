#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../object.h"
#include "../vertex.h"

enum class ShadingType {
	Flat,
	Phong
};

class Triangle: public Object
{
    public:
        Triangle(Vertex a, Vertex b, Vertex c, ShadingType s);

        virtual Hit intersect(Ray const &ray);

        virtual BBox boundingBox() const;

        Vertex va;
        Vertex vb;
        Vertex vc;

        ShadingType s = ShadingType::Flat;

    private:
        Point textureCoordAt(float beta, float gamma);
};

#endif
