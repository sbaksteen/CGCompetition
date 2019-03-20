#ifndef OBJTREE_H_
#define OBJTREE_H_

#include "object.h"
#include <vector>

struct IResult {
    ObjectPtr obj;
    Hit hit;
};

class ObjTree {
    public:
        BBox box;
        std::vector<ObjectPtr> objs;
        ObjTree* left = nullptr, *right = nullptr;

        ObjTree(std::vector<ObjectPtr> objs, std::vector<BBox> boxes, int recursion);

        IResult minhit(Ray const &ray);
    
    private:
        BBox computeBBox(std::vector<BBox> boxes);
};

#endif