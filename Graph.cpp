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

    initT();
}

void Graph::run() {
    auto best = cities;
    random_shuffle(cities.begin(), cities.end());
    auto i = 0;
    while (T > Tmin) {
        i++;
        next_step();
        if (i % 100 == 0)
            printf("%d: %.10f    %d    %d\n", i, T, getTotalDistance(), getTotalDistance(best));
        if (getTotalDistance(cities) < getTotalDistance(best)) {
            puts("zmieniono");
            best = cities;
        }
    }
    cout << i << endl;
    cities = best;
}

void Graph::next_step() {
    auto dim = (int) cities.size();
    for (auto i = 0; i < dim * dim / 4; i++) {
        auto temp = cities;
        swap(temp[randrange()], temp[randrange()]);
        auto diff = getTotalDistance(temp) - getTotalDistance();
        if (diff <= 0) {
            cities.swap(temp);
        } else if (random() < P(temp)) {
            cities.swap(temp);
        }
    }
    T = G();
}

double Graph::P(vector<City> &c) const {
    return exp((getTotalDistance() - getTotalDistance(c)) / T);
}

double Graph::G() const {
    return T * alpha;
}

int Graph::randrange() const {
    return (int) (rand() % cities.size());
}

double Graph::random() const {
    return double(rand() % 100) / 100;
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
    int total = getDistance(vec.back(), vec.front());
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

void Graph::initT() {
    vector<City> v;
    double mmax = 0;
    double mmin = 9999999;
    int dim = (int) cities.size();
    for (auto i = 0; i < dim * dim; i++) {
        v.clear();
        v = cities;
        random_shuffle(v.begin(), v.end());

        mmax = std::max(mmax, (double) getTotalDistance(v));
        mmin = std::min(mmin, (double) getTotalDistance(v));
    }

    T = -(mmax - mmin) / log(.9);
}


