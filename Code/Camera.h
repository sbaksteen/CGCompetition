#ifndef RAY_CAMERA_H
#define RAY_CAMERA_H

#include "ray.h"

class Camera {
public:
    int w, h;
    virtual Ray rayAt(double x, double y) = 0;
    void setDimensions(int w, int h) {
        this->w = w;
        this->h = h;
    }
};


#endif //RAY_CAMERA_H
