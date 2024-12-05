#pragma once

#include <utility>
#include "Event.hpp"

struct Arc {
    enum class Color{R, B};
    Arc(Arc* prev, Arc* next, Site* s, size_t le, size_t re, Color c)
     : prev(prev), next(next), site(s), l_edge(le), r_edge(re), color(c) {}
    Arc(Site* s, Color c)
     : site(s), color(c) {}

    // Hierarchy
    Arc* parent = nullptr;
    Arc* left = nullptr;
    Arc* right = nullptr;
    Arc* prev = nullptr;
    Arc* next = nullptr;
    // Diagram
    Site* site;
    size_t l_edge = NULL;
    size_t r_edge = NULL;
    Event* event = nullptr;
    // Only for balancing
    Color color;
};

struct Site {
    Site(size_t i, std::pair<double, double> p) : index(i), point(p) {}
    std::size_t index;
    std::pair<double, double> point;
    // Face* face;
};

std::pair<double, double> operator+(const std::pair<double, double>& a,const std::pair<double, double>& b) {
    return {a.first+b.first, a.second+b.second};
}
std::pair<double, double> operator-(const std::pair<double, double>& a,const std::pair<double, double>& b) {
    return {a.first-b.first, a.second-b.second};
}
std::pair<double, double> operator/(const std::pair<double, double>& a,double b) {
    return {a.first/b, a.second/b};
}