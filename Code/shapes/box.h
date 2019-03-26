#ifndef BOX_H_
#define BOX_H_

#include "closedObject.h"
#include "CSG/interval.h"
#include <vector>

class Box : public ClosedObject {
    public:
        virtual std::vector<Interval> intervals(Ray const &ray);
        
        virtual BBox boundingBox() const;

        Box(Point vmin, Point vmax) : vmin(vmin), vmax(vmax) {}
        Point vmin, vmax;
};

#endif