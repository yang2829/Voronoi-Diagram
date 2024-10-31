#pragma once

#include <cstddef>
#include <vector>

#include "VoronoiDiagram.h"
#include "define.h"

class Fortune
{
public:
    Fortune(size_t n, size_t w = 500, size_t h = 500);
    Fortune(std::vector<pdd> p, size_t w = 500, size_t h = 500);
    Fortune(const Fortune& d);

    void RunAlgo();

    void print_points() {diagram.print_points();}

private:
    VoronoiDiagram diagram;
    size_t width, height;
};

