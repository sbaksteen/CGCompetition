#ifndef OBJECT_H_
#define OBJECT_H_

#include "material.h"

// not really needed here, but deriving classes may need them
#include "hit.h"
#include "ray.h"
#include "triple.h"
#include "matrix.h"
#include "spacePartitioning/boundingBox.h"

#include <memory>
class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Object : public std::enable_shared_from_this<Object>
{
    public:
        Material material;

        virtual ~Object() = default;

        virtual Hit intersect(Ray const &ray) = 0;  // must be implemented
                                                    // in derived class

        virtual BBox boundingBox() const {
            return BBox::NO_BOX();
        }
};

#endif
