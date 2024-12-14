#include <iostream>

#include "Fortune.hpp"

int main()
{
    Fortune algo(8);
    algo.print_points();
    std::cout << "run algo1\n";
    algo.RunAlgo();
    std::cout << "run algo1 finish\n";
    algo.print_points();
    algo.print_edges();
    // std::cout << "\nalgo2:\n";
    // Fortune algo2({{1.5, 1.5}, {0.5, 0.5}, {1.5, 0.5}, {0.5, 1.5}});
    // algo2.print_points();
    // std::cout << "run algo2\n";
    // algo2.RunAlgo();
    // std::cout << "run algo2 finish\n";
    // algo2.print_points();
    // algo2.print_edges();
    return 0;
}
