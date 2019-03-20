#include "objtree.h"

#include <cmath>

#include <iostream>

using namespace std;

ObjTree::ObjTree(vector<ObjectPtr> objs, vector<BBox> boxes, int recursion) {
    if (recursion == 0 || objs.size() <= 1) {
        this->objs = objs;
        box = computeBBox(boxes);
        return;
    }
    BBox b = computeBBox(boxes);
    box = b;
    BBox bl, br;
    Vector lengths = b.vmax - b.vmin;
    if (lengths.x > lengths.y && lengths.x > lengths.z) {
        bl = BBox(b.vmin, Point(b.vmin.x + lengths.x/2, b.vmax.y, b.vmax.z));
        br = BBox(Point(b.vmin.x + lengths.x/2, b.vmin.y, b.vmin.z), b.vmax);
    } else if (lengths.y > lengths.z) {
        bl = BBox(b.vmin, Point(b.vmax.x, b.vmin.y + lengths.y/2, b.vmax.z));
        br = BBox(Point(b.vmin.x, b.vmin.y + lengths.y/2, b.vmin.z), b.vmax);
    } else {
        bl = BBox(b.vmin, Point(b.vmax.x, b.vmax.y, b.vmin.z + lengths.z/2));
        br = BBox(Point(b.vmin.x, b.vmin.y, b.vmin.z + lengths.z/2), b.vmax);
    }
    vector<ObjectPtr> lo, ro;
    vector<BBox> lb, rb;
    for (unsigned i = 0; i < objs.size(); i++) {
        BBox b = boxes[i];
        if (isnan(b.vmin.x)) {
            this->objs.push_back(objs[i]);
            box = BBox::NO_BOX();
        } else if (bl.vmax.x < b.vmin.x || bl.vmax.y < b.vmin.y || bl.vmax.z < b.vmin.z) {
            // doesn't overlap bl
            ro.push_back(objs[i]);
            rb.push_back(boxes[i]);
        } else {
            lo.push_back(objs[i]);
            lb.push_back(boxes[i]);
        }
    }
    left = new ObjTree(lo, lb, recursion-1);
    right = new ObjTree(ro, rb, recursion-1);
}

BBox ObjTree::computeBBox(vector<BBox> boxes) {
    BBox result = BBox(
        Point(
            numeric_limits<double>::infinity(),
            numeric_limits<double>::infinity(),
            numeric_limits<double>::infinity()
        ),
        Point(
            -numeric_limits<double>::infinity(),
            -numeric_limits<double>::infinity(),
            -numeric_limits<double>::infinity()
        )
    );
    for (unsigned i = 0; i < boxes.size(); i++) {
        BBox b = boxes[i];
        if (isnan(b.vmin.x)) continue;
        if (b.vmin.x < result.vmin.x) result.vmin.x = b.vmin.x;
        if (b.vmin.y < result.vmin.y) result.vmin.y = b.vmin.y;
        if (b.vmin.z < result.vmin.z) result.vmin.z = b.vmin.z;
        
        if (b.vmax.x > result.vmax.x) result.vmax.x = b.vmax.x;
        if (b.vmax.y > result.vmax.y) result.vmax.y = b.vmax.y;
        if (b.vmax.z > result.vmax.z) result.vmax.z = b.vmax.z;
    }
    return result;
}

IResult ObjTree::minhit(Ray const &ray) {
    if (!box.intersect(ray)) {
        IResult r = {nullptr, Hit::NO_HIT()};
        return r;
    }
    Hit h(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    if (left) {
        IResult a = left->minhit(ray),
                b = right->minhit(ray);
        if (a.hit.t < h.t) {
            h = a.hit;
            obj = a.obj;
        }
        if (b.hit.t < h.t) {
            h = b.hit;
            obj = b.obj;
        }
    }
    for (unsigned i = 0; i < objs.size(); i++) {
        Hit n = objs[i]->intersect(ray);
        if (n.t < h.t) {
            h = n;
            obj = objs[i];
        }
    }
    IResult r = {obj, h};
    return r;
}