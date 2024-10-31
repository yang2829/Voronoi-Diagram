#include "Fortune.h"

Fortune::Fortune(size_t n, size_t w, size_t h) : diagram(n,w,h) {
    width = w;
    height = h;
}
Fortune::Fortune(std::vector<pdd> p, size_t w, size_t h) : diagram(p) {
    width = w;
    height = h;
}
