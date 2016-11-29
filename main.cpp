#include <iostream>
#include <random>
#include <ctime>

#include "Graph.h"
#include "ATSP.h"
#include "FileSupport.h"

using namespace std;

int main(int argc, char **argv) {
    srand((unsigned int) time(nullptr));

    if (argc < 2) {
        printf("usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    string name = argv[1];
    auto g = Graph();
    FileSupport::loadTspFile(name, g);
    auto atsp = new ATSP(&g);

    auto annealing = atsp->Annealing();

    cout << endl << annealing << endl;

    return 0;
}
