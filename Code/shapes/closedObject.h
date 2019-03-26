#ifndef CLOSED_OBJECT_H_
#define CLOSED_OBJECT_H_

#include "../object.h"
#include "../hit.h"
#include "CSG/interval.h"
#include <vector>
#include <memory>

class ClosedObject;
typedef std::shared_ptr<ClosedObject> ClosedPtr;

class ClosedObject : public Object {
    public:
        virtual std::vector<Interval> intervals(Ray const &ray) = 0;

        virtual Hit intersect(Ray const &ray) {
            std::vector<Interval> ivs = intervals(ray);
            Hit min_hit = Hit(-1);
            for (int i = 0; i < ivs.size(); i++) {
                if (ivs[i].in.t > 0 && (ivs[i].in.t < min_hit.t || min_hit.t == -1)) {
                    min_hit = ivs[i].in;
                }
                if (ivs[i].out.t > 0 && (ivs[i].out.t < min_hit.t || min_hit.t == -1)) {
                    min_hit = ivs[i].out;
                }
            }
            if (min_hit.t == -1) return Hit::NO_HIT();
            return min_hit;
        }
};

#endif