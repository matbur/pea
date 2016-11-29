//
// Created on 20.05.16.
//

#pragma once

#include <cmath>
#include <vector>

#include "Graph.h"
#include "Permutation.h"

using namespace std;

class ATSP {
    Permutation *permutation;
    vector<int> cities;
    Graph *graph;

public:
    ATSP(Permutation *p, Graph *g);

    ATSP(Graph *g);

    /**
     * Rozwiazanie problemu metoda przegladu zupelnego.
     * Zawsze optymalny wynik.
     */
    static ATSP *BruteForce(const Graph *graph);

    /**
     * Rozwiazanie problemu algorytmem zachlannym.
     * Szybkie, ale nie ma gwarancji na optymalny wynik.
     */
    static ATSP *Greedy(const Graph *graph, int start = 0);

    void print();

    double T, Tmin = .01, alpha = .999;

    int Annealing();

    void run();

    void next_step();

    double P(vector<int> &c) const;

    double G() const;

    int randrange() const;

    double random() const;

    int getDistance(int c1, int c2) const;

    int getTotalDistance(vector<int> vec) const;

    void initT();
};
