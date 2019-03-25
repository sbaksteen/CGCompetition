#include "perspectiveCamera.h"

Ray PerspectiveCamera::rayAt(double x, double y) {
    double u = x - w/2.0;
    double v = y - h/2.0;
    Point p = pos + dist*dir + u*X*pixSize + v*Y*pixSize;
    return Ray(pos, (p - pos).normalized());
}
