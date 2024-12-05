#include <math.h>
#include "Fortune.hpp"

Fortune::Fortune(size_t n, size_t w, size_t h) : diagram(n,w,h), beachline() {
    width = w;
    height = h;
}

Fortune::Fortune(std::vector<std::pair<double, double>> p, size_t w, size_t h) : diagram(p), beachline() {
    width = w;
    height = h;
}

void Fortune::RunAlgo() {
    for (size_t i = 0; i < npoints(); i++)
        Equeue.push(new Event(&diagram.points[i]));

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
}

void Fortune::handleSiteEvent(Site* s) {
    if (beachline.root == nullptr) {
        beachline.root = new Arc(s, Arc::Color::B);
        return;
    }
    Arc* middleArc = beachline.locateArc(s->point.first, liney);
    if (middleArc->event != nullptr) {
        middleArc->event->deleted = true;
        middleArc->event = nullptr;
    }

    Arc* leftArc = new Arc(middleArc->prev, middleArc, middleArc->site, middleArc->l_edge, NULL, Arc::Color::R);
    if (leftArc->prev != nullptr)
        leftArc->prev->next = leftArc;
    Arc* rightArc = new Arc(middleArc, middleArc->next, middleArc->site, NULL, middleArc->r_edge, Arc::Color::R);
    if (rightArc->next != nullptr)
        rightArc->next->prev = rightArc;
    middleArc->prev = leftArc;
    middleArc->next = rightArc;
    size_t nedge = addSiteEdge(s, middleArc->site);
    middleArc->site = s;
    middleArc->l_edge = nedge;
    middleArc->r_edge = nedge+1;
    if (middleArc->left == nullptr) {
        middleArc->left = leftArc;
        leftArc->parent = middleArc;
    } else {
        leftArc->prev->right = leftArc;
        leftArc->parent = leftArc->prev;
    }
    beachline.insertFixup(leftArc);
    if (middleArc->right == nullptr) {
        middleArc->right = rightArc;
        rightArc->parent = middleArc;
    } else {
        rightArc->next->left = rightArc;
        rightArc->parent = rightArc->next;
    }
    beachline.insertFixup(rightArc);

    if (leftArc->prev != nullptr)
        addEvent(leftArc);
    if (rightArc->next != nullptr)
        addEvent(rightArc);
}

void Fortune::handleCircleEvent(std::pair<double, double> p, Arc* arc) {
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
    diagram.edges[arc->prev->r_edge].p2 = p;
    diagram.edges[arc->prev->r_edge].finish = true;
    diagram.edges[arc->next->l_edge].p2 = p;
    diagram.edges[arc->next->l_edge].finish = true;
    addCircleEdge(p, arc);
    beachline.remove(arc);
    delete arc;
    if (leftArc->prev != nullptr)
        addEvent(leftArc);
    if (rightArc->next != nullptr)
        addEvent(rightArc);
}

size_t Fortune::addSiteEdge(Site* s, Site* target) {
    size_t nedge = diagram.edges.size();
    double x1 = s->point.first, x2 = target->point.first, y2 = target->point.second;
    double t = x1 - x2;
    double y = ((t*t) / (2*(y2 - liney))) + ((y2 + liney)/2);
    std::pair<double, double> o1 = {-(s->point.second - target->point.second), s->point.first-target->point.first};
    if (o1.first > 0)
        o1 = -o1;
    diagram.edges.push_back(Edge({x1,y}, {NULL, NULL}, o1));
    diagram.edges.push_back(Edge({x1,y}, {NULL, NULL}, -o1));
    diagram.face[s->index].push_back(nedge);
    diagram.face[s->index].push_back(nedge+1);
    diagram.face[target->index].push_back(nedge);
    diagram.face[target->index].push_back(nedge+1);
    return nedge;
}

void Fortune::addCircleEdge(std::pair<double, double> p, Arc* arc) {
    size_t nedge = diagram.edges.size();
    std::pair<double, double> o1 = {-(arc->prev->site->point.second - arc->next->site->point.second), arc->prev->site->point.first-arc->next->site->point.first};
    if (o1.second > 0)
        o1 = -o1;
    diagram.edges.push_back(Edge(p, {NULL, NULL}, o1));
    diagram.face[arc->prev->site->index].push_back(nedge);
    diagram.face[arc->next->site->index].push_back(nedge);
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
    target->event = new Event(y, ePoint, target);
    Equeue.push(target->event);
}

bool Fortune::eventPoint(Arc* target, double& y) {
    std::pair<double, double> ePoint;
    std::pair<double, double> p1 = target->prev->site->point, p2 = target->site->point, p3 = target->next->site->point;
    std::pair<double, double> o1 = {-(p1.second-p2.second), p1.first-p2.first}, o2 = {-(p3.second-p2.second), p3.first-p2.first};
    std::pair<double, double> tmp1 = (p1+p2)/2, tmp2 = (p2+p3)/2;
    if (o1.first == 0) {
        if (o2.first == 0)
            return false;
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
            return false;
        double a1 = o1.second/o1.first;
        double a2 = o2.second/o2.first;
        double b1 = tmp1.second - a1*(tmp1.first);
        double b2 = tmp2.second - a2*(tmp2.first);
        ePoint.first = (b2-b1)/(a1-a2);
        ePoint.second = a1*ePoint.first+b1;
    }
    y = ePoint.second - std::sqrt((ePoint.first-p1.first)*(ePoint.first-p1.first) + (ePoint.second-p1.second)*(ePoint.second-p1.second));
    if (y > liney)
        return false;
}