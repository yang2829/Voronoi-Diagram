#include <math.h>
#include <random>
#include <ctime>
#include "Fortune.hpp"

Fortune::Fortune(size_t n, size_t w, size_t h, int seed) : face(n), beachline() {
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> d_x (0.0, double(w));
    std::uniform_real_distribution<double> d_y (0.0, double(h));
    points.reserve(n);
    for (size_t i = 0; i < n; i++) {
        points.push_back(Site(i, {d_x(generator), d_y(generator)}));
    }
    std::pair<double, double> nullpdd = {0,0};
    edges.push_back(Edge(nullpdd, nullpdd, nullpdd));
    width = w;
    height = h;
}

Fortune::Fortune(std::vector<std::pair<double, double>> p, size_t w, size_t h) : face(p.size()), beachline() {
    for (size_t i = 0; i < p.size(); i++) {
        points.push_back(Site(i, p[i]));
    }
    std::pair<double, double> nullpdd = {0,0};
    edges.push_back(Edge(nullpdd, nullpdd, nullpdd));
    width = w;
    height = h;
}

// Fortune::Fortune(const Fortune& other) {}

void Fortune::RunAlgo() {
    for (size_t i = 0; i < npoints(); i++)
        Equeue.push(new Event(&points[i], points[i].point.second));
    if (Equeue.empty())
        std::cout << "no event\n";

    while (!Equeue.empty()) {
        Event* e = Equeue.top();
        Equeue.pop();
        if (e->deleted) {
            delete(e);
            continue;
        }
        liney = e->y;
        if (e->site_type)
            handleSiteEvent(e->s);
        else
            handleCircleEvent(e->point, e->arc);
        delete(e);
    }
    completeEdge();
}

void Fortune::handleSiteEvent(Site* s) {
    if (info_out)
        std::cout << "handle site event: " << s->index << " x:" << s->point.first << " y:" << s->point.second << std::endl;
    if (beachline.isNil(beachline.root)) {
        beachline.root = new Arc(s, Arc::Color::B, beachline.Nil);
        return;
    }
    Arc* middleArc = beachline.locateArc(s->point.first, liney);
    if (middleArc->event != nullptr) {
        middleArc->event->deleted = true;
        middleArc->event = nullptr;
    }

    Arc* leftArc = new Arc(middleArc->prev, middleArc, middleArc->site, middleArc->l_edge, 0, Arc::Color::R, beachline.Nil);
    if (!beachline.isNil(leftArc->prev))
        leftArc->prev->next = leftArc;
    Arc* rightArc = new Arc(middleArc, middleArc->next, middleArc->site, 0, middleArc->r_edge, Arc::Color::R, beachline.Nil);
    if (!beachline.isNil(rightArc->next))
        rightArc->next->prev = rightArc;
    middleArc->prev = leftArc;
    middleArc->next = rightArc;
    middleArc->site = s;
    size_t nedge = addSiteEdge(leftArc->site, middleArc->site);
    if (nedge == 0)
        std::cout << "add edge error\n";
    middleArc->l_edge = nedge;
    middleArc->r_edge = nedge;
    leftArc->r_edge = nedge;
    rightArc->l_edge = nedge;
    if (beachline.isNil(middleArc->left)) {
        middleArc->left = leftArc;
        leftArc->parent = middleArc;
    } else {
        leftArc->prev->right = leftArc;
        leftArc->parent = leftArc->prev;
    }
    beachline.insertFixup(leftArc);
    if (beachline.isNil(middleArc->right)) {
        middleArc->right = rightArc;
        rightArc->parent = middleArc;
    } else {
        rightArc->next->left = rightArc;
        rightArc->parent = rightArc->next;
    }
    beachline.insertFixup(rightArc);
    if (!beachline.isNil(leftArc->prev))
        addEvent(leftArc);
    if (!beachline.isNil(rightArc->next))
        addEvent(rightArc);
}

void Fortune::handleCircleEvent(std::pair<double, double> p, Arc* arc) {
    if (info_out)
        std::cout << "handle circle event: x:" << p.first << " y:" << p.second << std::endl;
    Arc* leftArc = arc->prev;
    Arc* rightArc = arc->next;
    if (leftArc->event != nullptr) {
        leftArc->event->deleted = true;
        leftArc->event = nullptr;
    }
    if (rightArc->event != nullptr) {
        rightArc->event->deleted = true;
        rightArc->event = nullptr;
    }
    if (leftArc->r_edge != 0 && p != edges[leftArc->r_edge].d) {
        if (!edges[leftArc->r_edge].s_finish) {
            edges[leftArc->r_edge].s = p;
            edges[leftArc->r_edge].s_finish = true;
        }
    }
    if (arc->r_edge != 0 && p != edges[arc->r_edge].d) {
        if (!edges[arc->r_edge].s_finish) {
            edges[arc->r_edge].s = p;
            edges[arc->r_edge].s_finish = true;
        }
    }
    if (arc->l_edge != 0 && p != edges[arc->l_edge].s) {
        if (!edges[arc->l_edge].d_finish) {
            edges[arc->l_edge].d = p;
            edges[arc->l_edge].d_finish = true;
        }
    }
    if (rightArc->l_edge != 0 && p != edges[rightArc->l_edge].s) {
        if (!edges[rightArc->l_edge].d_finish) {
            edges[rightArc->l_edge].d = p;
            edges[rightArc->l_edge].d_finish = true;
        }
    }
    addCircleEdge(p, arc);
    beachline.remove(arc);
    delete arc;
    if (!beachline.isNil(leftArc->prev))
        addEvent(leftArc);
    if (!beachline.isNil(rightArc->next))
        addEvent(rightArc);
}

size_t Fortune::addSiteEdge(Site* s, Site* target) {
    size_t nedge = edges.size();
    double x1 = s->point.first, y1 = s->point.second, x2 = target->point.first, y2 = target->point.second;
    std::pair<double, double> o1 = {-(y1 - y2), x1 - x2};
    if (o1.second < 0)
        o1 = -o1;
    edges.push_back(Edge({(x1+x2)/2,(y1+y2)/2}, {0,0}, o1));
    face[s->index].push_back(nedge);
    face[target->index].push_back(nedge);
    return nedge;
}

void Fortune::addCircleEdge(std::pair<double, double> p, Arc* arc) {
    size_t nedge = edges.size();
    std::pair<double, double> o1 = {-(arc->prev->site->point.second - arc->next->site->point.second), arc->prev->site->point.first-arc->next->site->point.first};
    edges.push_back(Edge(p, {0,0}, o1));
    edges[nedge].s_finish = true;
    face[arc->prev->site->index].push_back(nedge);
    face[arc->next->site->index].push_back(nedge);
    arc->prev->r_edge = nedge;
    arc->next->l_edge = nedge;
}

void Fortune::addEvent(Arc* target) {
    if (target->prev->site == target->next->site)
        return;
    std::pair<double, double> ePoint;
    std::pair<double, double> p1 = target->prev->site->point, p2 = target->site->point, p3 = target->next->site->point;
    std::pair<double, double> o1 = {-(p1.second-p2.second), p1.first-p2.first}, o2 = {-(p3.second-p2.second), p3.first-p2.first};
    std::pair<double, double> tmp1 = (p1+p2)/2, tmp2 = (p2+p3)/2;
    if (o1.first == 0) {
        if (o2.first == 0)
            return;
        ePoint.first = (p1.first+p2.first)/2;
        double a2 = o2.second/o2.first;
        double b2 = tmp2.second - a2*(tmp2.first);
        ePoint.second = a2*ePoint.first + b2;
    } else if (o2.first == 0) {
        ePoint.first = (p2.first+p3.first)/2;
        double a1 = o1.second/o1.first;
        double b1 = tmp1.second - a1*(tmp1.first);
        ePoint.second = a1*ePoint.first + b1;
    } else {
        if (o1.second/o1.first == o2.second/o2.first)
            return;
        double a1 = o1.second/o1.first;
        double a2 = o2.second/o2.first;
        double b1 = tmp1.second - a1*(tmp1.first);
        double b2 = tmp2.second - a2*(tmp2.first);
        ePoint.first = (b2-b1)/(a1-a2);
        ePoint.second = a1*ePoint.first+b1;
    }
    double y = ePoint.second - std::sqrt((ePoint.first-p1.first)*(ePoint.first-p1.first) + (ePoint.second-p1.second)*(ePoint.second-p1.second));
    if (y > liney)
        return;
    bool isvalid = false;
    if ( ((p1.second<p2.second && p1.first<ePoint.first) || (p1.second>=p2.second && p2.first>ePoint.first)) &&
         ((p2.second<p3.second && p2.first<ePoint.first) || (p2.second>=p3.second && p3.first>ePoint.first)) )
         isvalid = true;
    if (!isvalid) {
        // report error
        return;
    }
    target->event = new Event(y, ePoint, target);
    if (info_out)
        std::cout << "creat circle event liney:" << y << " x:" << ePoint.first << " y:" << ePoint.second << std::endl;
    Equeue.push(target->event);
}

void Fortune::completeEdge() {
    for (size_t i = 1; i < edges.size(); i++) {
        if (info_out && (!edges[i].d_finish || !edges[i].s_finish))
            std::cout << edges[i].s_finish << " " << edges[i].d_finish << "\n"
                      << "s:" << edges[i].s.first << ", " << edges[i].s.second << " "
                      << "d:" << edges[i].d.first << ", " << edges[i].d.second << "\n"
                      << "v:" << edges[i].v.first << ", " << edges[i].v.second << "\n";
        if (!edges[i].s_finish) {
            if (!edges[i].d_finish) {
                double tmpx = 0, tmpy = 0;
                if (edges[i].v.first < 0) {
                    tmpx = (edges[i].s.first/(-edges[i].v.first));
                }
                else if (edges[i].v.first > 0) {
                    tmpx = ((width - edges[i].s.first)/(edges[i].v.first));
                }
                if (edges[i].v.second < 0) {
                    tmpy = (edges[i].s.second/(-edges[i].v.second));
                }
                else if (edges[i].v.second > 0) {
                    tmpy = ((height - edges[i].s.second)/(edges[i].v.second));
                }
                edges[i].d = edges[i].s + (edges[i].v * std::min(tmpx, tmpy));
            }
            edges[i].v = -edges[i].v;
            double tmpx = 0, tmpy = 0;
            if (edges[i].v.first < 0) {
                tmpx = (edges[i].s.first/(-edges[i].v.first));
            }
            else if (edges[i].v.first > 0) {
                tmpx = ((width - edges[i].s.first)/(edges[i].v.first));
            }
            if (edges[i].v.second < 0) {
                tmpy = (edges[i].s.second/(-edges[i].v.second));
            }
            else if (edges[i].v.second > 0) {
                tmpy = ((height - edges[i].s.second)/(edges[i].v.second));
            }
            edges[i].s = edges[i].s + (edges[i].v * std::min(tmpx, tmpy));
        }
        else if (!edges[i].d_finish) {
            double tmpx = 0, tmpy = 0;
            if (edges[i].v.first < 0) {
                tmpx = (edges[i].s.first/(-edges[i].v.first));
            }
            else if (edges[i].v.first > 0) {
                tmpx = ((width - edges[i].s.first)/(edges[i].v.first));
            }
            if (edges[i].v.second < 0) {
                tmpy = (edges[i].s.second/(-edges[i].v.second));
            }
            else if (edges[i].v.second > 0) {
                tmpy = ((height - edges[i].s.second)/(edges[i].v.second));
            }
            edges[i].d = edges[i].s + (edges[i].v * std::min(tmpx, tmpy));
        }
    }
}
