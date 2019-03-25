#ifndef RAY_ORTHOGRAPHICCAMERA_H
#define RAY_ORTHOGRAPHICCAMERA_H


#include "../camera.h"

class OrthographicCamera : public Camera {
public:
    Point pos;
    Vector dir;
    double pixSize;

    Vector X;
    Vector Y;
    OrthographicCamera(Point pos, Vector d, double pixSize)
    : pos(pos),
      dir(d.normalized()),
      pixSize(pixSize) {
        X = dir.cross(Vector(0, 1, 0));
        if (!X.length_2()) {
            X = dir.cross(Vector(0, 1, 0.1));
        }
        X.normalize();

        Y = dir.cross(X);
    }

    Ray rayAt(double x, double y) override;
};


#endif //RAY_ORTHOGRAPHICCAMERA_H
