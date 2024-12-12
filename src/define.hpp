#pragma once

#include <utility>
#include <iostream>

struct Site {
    Site(size_t i, std::pair<double, double> p) : index(i), point(p) {}
    std::size_t index;
    std::pair<double, double> point;
};

struct Edge{
    Edge(std::pair<double, double> a, std::pair<double, double> b, std::pair<double, double> v) : s(a), d(b), v(v) {}
    std::pair<double, double> s;
    std::pair<double, double> d;
    std::pair<double, double> v;
    bool s_finish = false;
    bool d_finish = false;
};


inline std::pair<double, double> operator+(const std::pair<double, double>& a, const std::pair<double, double>& b) {
    return {a.first+b.first, a.second+b.second};
}
inline std::pair<double, double> operator-(const std::pair<double, double>& a, const std::pair<double, double>& b) {
    return {a.first-b.first, a.second-b.second};
}
inline std::pair<double, double> operator/(const std::pair<double, double>& a, double b) {
    return {a.first/b, a.second/b};
}
inline std::pair<double, double> operator-(const std::pair<double, double>& a) {
    return {-a.first, -a.second};
}