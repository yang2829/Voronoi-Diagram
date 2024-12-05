#include <iostream>

#include "Fortune.hpp"

int main()
{
    Fortune algo(50);
    algo.print_points();
    Fortune algo2({{1.5, 1.5}, {0.5, 0.5}, {1.5, 0.5}, {0.5, 1.5}});
    algo2.print_points();
    return 0;
}
