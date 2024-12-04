#pragma once

#include <utility>
#include "Event.hpp"

struct Arc {
    enum class Color{R, B};
    Arc(Arc* p, Arc* l, Arc* r, Arc* prev, Arc* next, Site* s, std::pair<double, double>* le, std::pair<double, double>* re, Event* e, Color c)
     : parent(p), left(l), right(r), prev(prev), next(next), site(s), l_edge(le), r_edge(re), event(e), color(c) {}
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
    std::pair<double, double>* l_edge = nullptr;
    std::pair<double, double>* r_edge = nullptr;
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