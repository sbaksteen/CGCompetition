#ifndef HIT_H_
#define HIT_H_

#include "triple.h"
#include "material.h"
#include <limits>

class Hit
{
    public:
        double t;   // distance of hit
        Vector N;   // Normal at hit
        Point texPt;
        Material* mat;

        Hit(double time, Vector const &normal, Point texPt = Point(0, 0, 0), Material* mat = nullptr)
        :
            t(time),
            N(normal),
            texPt(texPt),
            mat(mat)
        {}

        static Hit const NO_HIT()
        {
            static Hit no_hit(std::numeric_limits<double>::quiet_NaN(),
                              Vector(std::numeric_limits<double>::quiet_NaN(),
                                     std::numeric_limits<double>::quiet_NaN(),
                                     std::numeric_limits<double>::quiet_NaN()),
                              Point(std::numeric_limits<double>::quiet_NaN(),
                                     std::numeric_limits<double>::quiet_NaN(),
                                     std::numeric_limits<double>::quiet_NaN()));
            return no_hit;
        }
};

#endif
