//
// Created by matbur on 08.10.16.
//

#include "Graph.h"

Graph::Graph(File file) {
    init(&file);
}

Graph::Graph(File *file) {
    init(file);
}

Graph::Graph(string filename) {
    init(new File(filename));
}

void Graph::init(File *file) {
    points = file->dimension;
    for (auto i: file->node_coord_section) {
        cities.push_back(City(i));
    }
    random_shuffle(cities.begin(), cities.end());
}

void Graph::run() {
    auto i = 0;
    while (T > Tmin) {
        i++;
        next_step();
    }
    cout << i << endl;
}

void Graph::next_step() {
    auto temp = cities;
    swap(temp[randrange()], temp[randrange()]);
    if (getTotalDistance(temp) < getTotalDistance() or
        random() < P(temp)) {
        cities.swap(temp);
    }
    G();
}

double Graph::P(vector<City> &c) const {
    return exp(-(getTotalDistance(c) - getTotalDistance()) / T);
}

double Graph::G() {
    T *= alpha;
}

int Graph::randrange() const {
    return (int) (rand() % cities.size());
}

double Graph::random() const {
    return double(rand()) / RAND_MAX;
}

int Graph::getDistance(const City &c1, const City &c2) const {
    int xd = c1.x - c2.x;
    int yd = c1.y - c2.y;
    return int(sqrt(xd * xd + yd * yd) + .5);
}

int Graph::getTotalDistance() const {
    return getTotalDistance(cities);
}

int Graph::getTotalDistance(vector<City> vec) const {
    int total = 0;
    for (auto it = vec.begin() + 1; it != vec.end(); it++) {
        total += getDistance(*(it - 1), *it);
    }
    return total;
}

void Graph::print() const {
    for (auto i = 0; i < points; i++) {
        cities[i].print();
        puts("");
    }
}

void Graph::print_permutation() const {
    printf("<%d", cities[0].index);
    for (auto it = cities.begin() + 1; it != cities.end(); it++) {
        printf(", %d", it->index);
    }
    printf(">");
}


