#pragma once

#include <cstddef>
#include <vector>
#include <queue>

#include "Voronoi.hpp"
#include "define.hpp"
#include "Event.hpp"
#include "Beachline.hpp"

class Fortune
{
public:
    Fortune(size_t n, size_t w = 500, size_t h = 500);
    Fortune(std::vector<std::pair<double, double>> p, size_t w = 500, size_t h = 500);
    Fortune(const Fortune& d);

    void RunAlgo();
    size_t npoints() { return diagram.npoints(); }

    void print_points() {diagram.print_points();}

private:
    Voronoi diagram;
    size_t width, height;
    double liney;
    Beachline beachline;
    std::priority_queue<Event *, std::vector<Event *>, Event::CompareEvent> Equeue;

    void handleSiteEvent(Site* s);
    void handleCircleEvent(std::pair<double, double> p, Arc* arc);
    size_t addSiteEdge(Site* s, Site* target);
    void addCircleEdge(std::pair<double, double> p, Arc* arc);
    void addEvent(Arc* target);
    bool eventPoint(Arc* target, double& y);
};

