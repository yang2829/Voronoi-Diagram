#pragma once

#include "Arc.hpp"

class Beachline
{
public:
    Beachline() {
        Nil = new Arc(nullptr, Arc::Color::B, nullptr);
        root = Nil;
    }
    ~Beachline() {free(root); delete(Nil); }
    bool isNil(const Arc* a) const { return a == Nil; }
    Arc* locateArc(double x, double liney);
    double intersectionArc(std::pair<double, double> p1, std::pair<double, double> p2, double liney);
    void remove(Arc* z);

    friend class Fortune;

private:
    Arc* minimum(Arc* x) const;
    void transplant(Arc* u, Arc* v);
    void insertFixup(Arc* z);
    void removeFixup(Arc* x);
    void leftRotate(Arc* x);
    void rightRotate(Arc* y);
    void free(Arc* arc);
    Arc* root;
    Arc* Nil;
};