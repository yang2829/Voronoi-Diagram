#include <random>
#include <ctime>

#include "Voronoi.hpp"

Voronoi::Voronoi(size_t n, size_t w, size_t h, int seed) {
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> d_x (0.0, double(w));
    std::uniform_real_distribution<double> d_y (0.0, double(h));
    points.reserve(n);
    for (size_t i = 0; i < n; i++) {
        points.push_back(Site(i, {d_x(generator), d_y(generator)}));
    }
    edges.push_back({{0,0},{0,0}});
}
Voronoi::Voronoi(std::vector<std::pair<double, double>> p) {
    for (size_t i = 0; i < p.size(); i++) {
        points.push_back(Site(i, p[i]));
    }
    edges.push_back({{0,0},{0,0}});
}
