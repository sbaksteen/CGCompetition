#ifndef HIT_H_
#define HIT_H_

#include "triple.h"
#include <limits>

class Hit
{
    public:
        double t;   // distance of hit
        Vector N;   // Normal at hit
        Point texPt;

        Hit(double time, Vector const &normal, Point texPt)
        :
            t(time),
            N(normal),
            texPt(texPt)
        {}

        Hit(double time, Vector const &normal)
        :
            t(time),
            N(normal)
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
