#pragma once

#include <cstddef>
#include <vector>
#include <queue>
#include <iostream>

#include "define.hpp"
#include "Event.hpp"
#include "Beachline.hpp"
#include "Arc.hpp"

class Fortune
{
public:
    Fortune(size_t n, size_t w = 500, size_t h = 500, int seed = 1512);
    Fortune(std::vector<std::pair<double, double>> p, size_t w = 500, size_t h = 500);
    // Fortune(const Fortune& other);

    void RunAlgo();
    void completeEdge();
    size_t npoints() { return points.size(); }
    size_t getw() { return width; }
    size_t geth() { return height; }

    std::vector<Site> get_points() { return points; }
    std::vector<Edge> get_edges() { return edges; }
    void print_points() {
        for (size_t i = 0; i < points.size(); i++) {
            std::cout << i << ": " << points[i].point.first << " " << points[i].point.second << std::endl;
        }
    }
    void print_edges() {
        for (size_t i = 0; i < edges.size(); i++) {
            std::cout << i << ": status: " << edges[i].s_finish << " " << edges[i].d_finish << std::endl;
            std::cout << "{" << edges[i].s.first << ", " << edges[i].s.second << "}  -->  ";
            std::cout << "{" << edges[i].d.first << " " << edges[i].d.second << "}\n";
            std::cout << "v: " << edges[i].v.first << ", " << edges[i].v.second << std::endl << std::endl;
        }
    }
    bool info_out = false;

private:
    size_t width, height;
    double liney;
    std::vector<Site> points;
    std::vector<Edge> edges;
    std::vector<std::vector<size_t>> face;
    Beachline beachline;
    std::priority_queue<Event *, std::vector<Event *>, Event::CompareEvent> Equeue;

    void handleSiteEvent(Site* s);
    void handleCircleEvent(std::pair<double, double> p, Arc* arc);
    size_t addSiteEdge(Site* s, Site* target);
    void addCircleEdge(std::pair<double, double> p, Arc* arc);
    void addEvent(Arc* target);
};
