#include <iostream>
#include <random>
#include <ctime>

#include "Graph.h"

using namespace std;

int main(int argc, char **argv) {
    srand((unsigned int) time(nullptr));

    if (argc < 2) {
        printf("usage: %s <filename>", argv[0]);
        exit(1);
    }

    auto g = new Graph(argv[1]);

    g->run();

    cout << endl << g->getTotalDistance() << endl;
    g->print_permutation();

    return 0;
}