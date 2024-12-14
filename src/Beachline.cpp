#include <math.h>
#include "Beachline.hpp"

Arc* Beachline::locateArc(double x, double liney) {
    Arc* node = root;
    bool found = false;
    while (!found)
    {
        double breakpointLeft = -std::numeric_limits<double>::infinity();
        double breakpointRight = std::numeric_limits<double>::infinity();
        if (!isNil(node->prev))
           breakpointLeft =  intersectionArc(node->prev->site->point, node->site->point, liney);
        if (!isNil(node->next))
            breakpointRight = intersectionArc(node->site->point, node->next->site->point, liney);
        if (x < breakpointLeft)
            node = node->left;
        else if (x > breakpointRight)
            node = node->right;
        else
            found = true;
    }
    return node;
}

double Beachline::intersectionArc(std::pair<double, double> p1, std::pair<double, double> p2, double liney) {
    double x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
    double d1 = 1.0 / (y1 - liney);
	double d2 = 1.0 / (y2 - liney);
	double double_a = (d1 - d2);
	double b = x2 * d2 - x1 * d1;
	double double_c = (y1 * y1 + x1 * x1 - liney * liney) * d1 - (y2 * y2 + x2 * x2 - liney * liney) * d2;
	double delta = b * b - double_a * double_c;
    double ans1 = (-b + std::sqrt(delta)) / double_a;
    double ans2 = (-b - std::sqrt(delta)) / double_a;
    if (y1 < y2) return std::max(ans1, ans2);
    else return std::min(ans1, ans2);
}

void Beachline::remove(Arc* z) {
    Arc* y = z;
    Arc::Color yOriginalColor = y->color;
    Arc* x;
    if (isNil(z->left))
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (isNil(z->right))
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y; // Because x could be Nil
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yOriginalColor == Arc::Color::B)
        removeFixup(x);
    // Update next and prev
    if (!isNil(z->prev))
        z->prev->next = z->next;
    if (!isNil(z->next))
        z->next->prev = z->prev;
}

Arc* Beachline::minimum(Arc* x) const {
    while (!isNil(x->left))
        x = x->left;
    return x;
}

void Beachline::transplant(Arc* u, Arc* v) {
    if (isNil(u->parent))
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void Beachline::insertFixup(Arc* z) {
    while (z->parent->color == Arc::Color::R) {
        if (z->parent == z->parent->parent->left) {
            Arc* y = z->parent->parent->right;
            // Case 1
            if (y->color == Arc::Color::R) {
                z->parent->color = Arc::Color::B;
                y->color = Arc::Color::B;
                z->parent->parent->color = Arc::Color::R;
                z = z->parent->parent;
            }
            else {
                // Case 2
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3
                z->parent->color = Arc::Color::B;
                z->parent->parent->color = Arc::Color::R;
                rightRotate(z->parent->parent);
            }
        }
        else {
            Arc* y = z->parent->parent->left;
            // Case 1
            if (y->color == Arc::Color::R) {
                z->parent->color = Arc::Color::B;
                y->color = Arc::Color::B;
                z->parent->parent->color = Arc::Color::R;
                z = z->parent->parent;
            }
            else {
                // Case 2
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3
                z->parent->color = Arc::Color::B;
                z->parent->parent->color = Arc::Color::R;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = Arc::Color::B;
}

void Beachline::removeFixup(Arc* x) {
    while (x != root && x->color == Arc::Color::B) {
        Arc* w;
        if (x == x->parent->left) {
            w = x->parent->right;
            // Case 1
            if (w->color == Arc::Color::R) {
                w->color = Arc::Color::B;
                x->parent->color = Arc::Color::R;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            // Case 2
            if (w->left->color == Arc::Color::B && w->right->color == Arc::Color::B) {
                w->color = Arc::Color::R;
                x = x->parent;
            }
            else {
                // Case 3
                if (w->right->color == Arc::Color::B) {
                    w->left->color = Arc::Color::B;
                    w->color = Arc::Color::R;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4
                w->color = x->parent->color;
                x->parent->color = Arc::Color::B;
                w->right->color = Arc::Color::B;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            w = x->parent->left;
            // Case 1
            if (w->color == Arc::Color::R) {
                w->color = Arc::Color::B;
                x->parent->color = Arc::Color::R;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            // Case 2
            if (w->left->color == Arc::Color::B && w->right->color == Arc::Color::B) {
                w->color = Arc::Color::R;
                x = x->parent;
            }
            else {
                // Case 3
                if (w->left->color == Arc::Color::B) {
                    w->right->color = Arc::Color::B;
                    w->color = Arc::Color::R;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4
                w->color = x->parent->color;
                x->parent->color = Arc::Color::B;
                w->left->color = Arc::Color::B;
                rightRotate(x->parent);
                x = root;
            } 
        }
    }
    x->color = Arc::Color::B;
}

void Beachline::leftRotate(Arc* x) {
    Arc* y = x->right;
    x->right = y->left;
    if (!isNil(y->left))
        y->left->parent = x;
    y->parent = x->parent;
    if (isNil(x->parent))
        root = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void Beachline::rightRotate(Arc* y) {
    Arc* x = y->left;
    y->left = x->right;
    if (!isNil(x->right))
        x->right->parent = y;
    x->parent = y->parent;
    if (isNil(y->parent))
        root = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void Beachline::free(Arc* x) {
    if (isNil(x))
        return;
    else {
        free(x->left);
        free(x->right);
        delete x;
    }
}