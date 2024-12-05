#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

#include "define.hpp"


class Voronoi
{
public:
    // constructor
    Voronoi(size_t n, size_t w, size_t h, int seed = 1512);
    Voronoi(std::vector<std::pair<double, double>> p);
    Voronoi(const Voronoi& d);

    void print_points() {
        for (size_t i = 0; i < points.size(); i++) {
            std::cout << i << ": " << points[i].point.first << " " << points[i].point.second << std::endl;
        }
    }

    size_t npoints() { return points.size(); }

    friend class Fortune;

private:
    std::vector<Site> points;
    std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> edges;
    std::vector<std::vector<size_t>> face;
};
