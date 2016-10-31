#include <iostream>
#include <random>
#include <ctime>

#include "Graph.h"

int main() {
    srand((unsigned int) time(nullptr));

//    auto g = new Graph("data/my10.tsp");
//    auto g = new Graph("data/eil51.tsp");
    auto g = new Graph("data/st70.tsp");

    g->run();

    cout << endl << g->getTotalDistance() << endl;
    g->print_permutation();

    return 0;
}