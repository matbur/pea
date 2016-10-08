//
// Created by matbur on 08.10.16.
//

#pragma once

#include <iostream>
#include <vector>
#include <random>

#include "City.h"
#include "File.h"

using namespace std;

class Graph {
public:
    vector<City> cities;
    int points;
    double T = 1000,
            Tmin = 1,
            alpha = .99;

    Graph(File file);

    Graph(File *file);

    Graph(string filename);

    void init(File *file);

    void run();

    void next_step();

    double P(vector<City> &c) const;

    double G();

    int randrange() const;

    double random() const;

    int getDistance(const City &c1, const City &c2) const;

    int getTotalDistance() const;

    int getTotalDistance(vector<City> vec) const;

    void print() const;

    void print_permutation() const;
};
