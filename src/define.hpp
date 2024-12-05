#pragma once

#include <utility>
#include <iostream>

struct Site {
    Site(size_t i, std::pair<double, double> p) : index(i), point(p) {}
    std::size_t index;
    std::pair<double, double> point;
};

struct Edge{
    Edge(std::pair<double, double> a, std::pair<double, double> b, std::pair<double, double> v) : p1(a), p2(b), v(v) {}
    std::pair<double, double> p1;
    std::pair<double, double> p2;
    std::pair<double, double> v;
    bool finish = false;
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