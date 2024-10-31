#include <random>
#include <ctime>

#include "VoronoiDiagram.h"

VoronoiDiagram::VoronoiDiagram(size_t n, size_t w, size_t h, int seed) {
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> d_x (0.0, double(w));
    std::uniform_real_distribution<double> d_y (0.0, double(h));
    points.reserve(n);
    for (size_t i = 0; i < n; i++) {
        points.push_back({d_x(generator), d_y(generator)});
    }
}
VoronoiDiagram::VoronoiDiagram(std::vector<pdd> p) : points(p) {}
