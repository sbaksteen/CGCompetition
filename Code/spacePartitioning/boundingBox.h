#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_

#include "../ray.h"
#include <cmath>
#include <limits>

class BBox {
    public:
        bool intersect(Ray const &ray) {
            if (std::isnan(vmin.x)) return true;
            Vector tmin = (vmin - ray.O) / ray.D;
            Vector tmax = (vmax - ray.O) / ray.D;
            
            if (tmin.x > tmax.x) {
                double temp = tmin.x;
                tmin.x = tmax.x;
                tmax.x = temp;
            }
            if (tmin.y > tmax.y) {
                double temp = tmin.y;
                tmin.y = tmax.y;
                tmax.y = temp;
            }
            if (tmin.z > tmax.z) {
                double temp = tmin.z;
                tmin.z = tmax.z;
                tmax.z = temp;
            }

            double low = fmax(tmin.x, fmax(tmin.y, tmin.z));
            double hi = fmin(tmax.x, fmin(tmax.y, tmax.z));

            return low < hi && (low > 0 || hi > 0);
        }

        BBox() {
            vmin = Point(
                std::numeric_limits<double>::infinity(),
                std::numeric_limits<double>::infinity(),
                std::numeric_limits<double>::infinity()
            );
            vmax = Point(
                -std::numeric_limits<double>::infinity(),
                -std::numeric_limits<double>::infinity(),
                -std::numeric_limits<double>::infinity()
            );
        }

        BBox(Point vmin, Point vmax) : vmin(vmin), vmax(vmax) {}
        Point vmin, vmax;

        static BBox const NO_BOX() {
            return BBox(Point(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()),
                        Point(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()));
        }
};

#endif