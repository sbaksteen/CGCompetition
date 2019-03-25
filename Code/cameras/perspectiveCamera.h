#ifndef RAY_PERSPECTIVECAMERA_H
#define RAY_PERSPECTIVECAMERA_H

#include "../camera.h"
#include "../triple.h"

class PerspectiveCamera : public Camera {
public:
    Point pos;
    Vector dir;
    double dist;
    double pixSize;

    Vector X;
    Vector Y;
    PerspectiveCamera(Point pos, Vector d, double dist, double pixSize = 1)
    : pos(pos),
      dir(d.normalized()),
      dist(dist),
      pixSize(pixSize) {
        X = dir.cross(Vector(0, 1, 0));
        if (!X.length_2()) {
            X = dir.cross(Vector(0, 1, 0.1));
        }
        X.normalize();

        Y = dir.cross(X);
    }

    virtual Ray rayAt(double x, double y);
};


#endif //RAY_PERSPECTIVECAMERA_H
