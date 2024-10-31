#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

#include "define.h"


class VoronoiDiagram
{
public:
    struct Site
    {
        std::size_t index;
        pdd point;
    };

    // constructor
    VoronoiDiagram(size_t n, size_t w, size_t h, int seed = 1512);
    VoronoiDiagram(std::vector<pdd> p);
    VoronoiDiagram(const VoronoiDiagram& d);

    void print_points() {
        for (size_t i = 0; i < points.size(); i++) {
            std::cout << i << ": " << points[i].x << " " << points[i].y << std::endl;
        }
    }

private:
    std::vector<pdd> points;
};
