#pragma once

#include <functional>
#include "define.hpp"

class Event
{
public:
    // Site event
    Event(Site* s) : site_type(true), deleted(false), y(s->point.second), s(s) {}
    // Circle event
    Event(double y, std::pair<double, double> point, Arc* arc) : site_type(false), deleted(false), y(y), point(point), arc(arc) {}

    struct CompareEvent {
		bool operator() (const Event* l, const Event* r) const { return (l->y < r->y); }
	};
    friend class Fortune;

private:
    const bool site_type;
    bool deleted;
    double y;
    // Site event
    Site* s;
    // Circle event
    std::pair<double, double> point;
    Arc* arc;

};
