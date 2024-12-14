# pragma once

#include "define.hpp"
#include "Event.hpp"

class Event;

struct Arc {
    enum class Color{R, B};
    Arc(Arc* prev, Arc* next, Site* s, size_t le, size_t re, Color c, Arc* Nil)
     : prev(prev), next(next), site(s), l_edge(le), r_edge(re), color(c) {
        parent = Nil;
        left = Nil;
        right = Nil;
        event = nullptr;
    }
    Arc(Site* s, Color c, Arc* Nil)
     : site(s), color(c) {
        parent = Nil;
        left = Nil;
        right = Nil;
        prev = Nil;
        next = Nil;
        event = nullptr;
    }

    // Hierarchy
    Arc* parent;
    Arc* left;
    Arc* right;
    Arc* prev;
    Arc* next;
    // Diagram
    Site* site;
    size_t l_edge = 0;
    size_t r_edge = 0;
    Event* event;
    // Only for balancing
    Color color;
};