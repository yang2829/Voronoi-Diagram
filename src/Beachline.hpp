#pragma once

#include "define.hpp"

class Beachline
{
public:
    Beachline() : root(nullptr) {}
    friend class Fortune;
    Arc* locateArc(double x, double liney);
    double intersectionArc(std::pair<double, double> p1, std::pair<double, double> p2, double liney);
    void remove(Arc* z);

private:
    Arc* minimum(Arc* x) const;
    void transplant(Arc* u, Arc* v);
    void insertFixup(Arc* z);
    void removeFixup(Arc* x);
    void leftRotate(Arc* x);
    void rightRotate(Arc* y);
    Arc* root;
};