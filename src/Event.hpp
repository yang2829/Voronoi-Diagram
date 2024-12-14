#pragma once

#include <functional>
#include "define.hpp"
#include "Arc.hpp"

struct Arc;

class Event
{
public:
    // Site event
    Event(Site* s, double y) : site_type(true), y(y), s(s) {}
    // Circle event
    Event(double y, std::pair<double, double> point, Arc* arc) : site_type(false), y(y), point(point), arc(arc) {}

    struct CompareEvent {
		bool operator() (const Event* l, const Event* r) const { return (l->y < r->y); }
	};
    friend class Fortune;

private:
    const bool site_type;
    bool deleted = false;
    double y;
    // Site event
    Site* s = nullptr;
    // Circle event
    std::pair<double, double> point;
    Arc* arc = nullptr;

};
