#include "interval.h"

using namespace std;


vector<Interval> simplify(vector<Interval> intervals) {
    bool change = true;
    vector<Interval> result = intervals;
    while (change) {
        change = false;
        intervals = result;
        result = vector<Interval>();
        for (int i = 0; i < intervals.size(); i++) {
            bool simp = false;
            for (int j = i+1; j < intervals.size(); j++) {
                vector<Interval> ij = intervals[i] + intervals[j];
                if (ij.size() == 1) {
                    simp = true;
                    change = true;
                    result.push_back(ij[0]);
                    break;
                }
            }
            if (!simp) {
                result.push_back(intervals[i]);
            }
        }
    }
    return result;
}

void smartAdd(vector<Interval> &intervals, Interval ni) {
    intervals.push_back(ni);
    vector<Interval> simp = simplify(intervals);
    intervals = simp;
}

vector<Interval> Interval::operator +(Interval other) {
    vector<Interval> result;
    if (other < *this) {
        result.push_back(*this);
    } else if (*this < other) {
        result.push_back(other);
    } else if (leftInside(other)) {
        result.push_back(Interval(other.in, out));
    } else if (rightInside(other)) {
        result.push_back(Interval(in, other.out));
    } else {
        result.push_back(*this);
        result.push_back(other);
    }
    return result;
}

vector<Interval> Interval::operator -(Interval other) {
    vector<Interval> result;
    if (*this < other) {
        return result;
    }
    if (other < *this) {
        result.push_back(Interval(in, other.in));
        result.push_back(Interval(other.out, out));
    } else if (other.rightInside(*this)) {
        result.push_back(Interval(other.out, out));
    } else if (other.leftInside(*this)) {
        result.push_back(Interval(in, other.in));
    } else {
        result.push_back(*this);
    }
    return result;
}

vector<Interval> Interval::operator *(Interval other) {
    vector<Interval> result;
    if (*this < other) {
        result.push_back(*this);
    } else if (other < *this) {
        result.push_back(other);
    } else if (leftInside(other)) {
        result.push_back(Interval(in, other.out));
    } else if (rightInside(other)) {
        result.push_back(Interval(other.in, out));
    }
    return result;
}

bool Interval::leftInside(Interval other) {
    return in.t > other.in.t && in.t < other.out.t;
}

bool Interval::rightInside(Interval other) {
    return out.t > other.in.t && out.t < other.out.t;
}

bool Interval::operator <(Interval other) {
    return leftInside(other) && rightInside(other);
}

bool Interval::operator >(Interval other) {
    return other.leftInside(*this) && other.rightInside(*this);
}