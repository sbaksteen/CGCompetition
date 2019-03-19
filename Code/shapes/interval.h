#ifndef INTERVAL_H_
#define INTERVAL_H_
#include <vector>
#include "../hit.h"
using namespace std;

class Interval {
    public:
        Hit in;
        Hit out;

        Interval(Hit in, Hit out) : in(in), out(out) {}

        vector<Interval> operator +(Interval other);
        vector<Interval> operator *(Interval other);
        vector<Interval> operator -(Interval other);
        bool operator <(Interval other);
        bool operator >(Interval other);

        bool leftInside(Interval other);
        bool rightInside(Interval other);
};

void smartAdd(vector<Interval> &intervals, Interval i);

#endif
