#ifndef POLYROOTS_H_
#define POLYROOTS_H_
#include <vector>

std::vector<double> solveQuadratic(double a, double b, double c);

std::vector<double> solveCubic(double a, double b, double c, double d);

std::vector<double> solveQuartic(double a, double b, double c, double d, double e);

double minPos(std::vector<double> v);

#endif