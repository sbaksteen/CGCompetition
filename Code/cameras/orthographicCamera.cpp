#include "orthographicCamera.h"

Ray OrthographicCamera::rayAt(double x, double y) {
    double u = x - w/2.0;
    double v = y - h/2.0;
    Point p = pos + u*X*pixSize + v*Y*pixSize;
    return Ray(p, dir);
}
