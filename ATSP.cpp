//
// Created on 20.05.16.
//

#include <algorithm>
#include "ATSP.h"

ATSP::ATSP(Permutation *p, Graph *g) : permutation(p), graph(g) {}

ATSP *ATSP::BruteForce(const Graph *graph) {
    auto n = graph->getPoints();                                            // ilosc miast do odwiedzenia

    Graph *tempGraph;                                                       // tymczasowy graf
    auto *minGraph = new Graph(n);                                          // graf z najkrotsza droga

    auto permutation = new Permutation(n);                                  // permutacja do iteracji
    auto minPerm = new Permutation(n);                                      // permutacja z najkrotsza droga

    do {
        tempGraph = new Graph(n);                                           // nowy, pusty graf
        for (auto i = 0; i < n; i++) {                                      // przepisanie krawedzi wg. permutacji
            auto from = (*permutation)[i];
            auto to = (*permutation)[(i + 1) % n];                          // nastepny element permutacji
            auto weight = graph->getWeight(from, to);
            tempGraph->addEdge(from, to, weight, true);                     // dodanie elementu
        }

        if (*tempGraph < *minGraph) {                                       // jesli nowa droga krotsza od starej
            *minGraph = *tempGraph;                                         // nadpisanie grafu koncowego
            *minPerm = *permutation;                                        // nadpisanie permutacji koncowej
        }
        delete tempGraph;
    } while (permutation->next());                                          // nastepna permutacja

    delete permutation;
    return new ATSP(minPerm, minGraph);
}

ATSP *ATSP::Greedy(const Graph *graph, int start /*= 0*/) {
    auto n = graph->getPoints();                                            // ilosc miast do odwiedzenia

    if (start >= n)                                                         // wiercholek starowy musi istniec
        return nullptr;

    auto minGraph = new Graph(n);                                           // graf z najkrotsza droga
    int *permTab = new int[n];                                              // permutacja z najkrotsza droga

    auto visited = new bool[n]{false};                                      // tablica odwiedzonych

    int min, temp, current = start, next = start;
    for (auto i = 0; i < n; i++) {
        visited[current] = true;                                            // oznacz jako odwiedzone
        permTab[i] = current;                                               // ustawienie elementu w permutacji
        min = INT_MAX;                                                      // zeby potem zmniejszyc
        for (auto col = 0; col < n; col++) {
            temp = graph->getWeight(current, col);
            if (temp != -1 and temp < min and !visited[col]) {              // jesli jeszcze wierzcholek nie odwiedzony
                min = temp;                                                 // wartosc minimalnej krawedzi
                next = col;                                                 // indeks minimalnej krawedzi
            }
        }
        minGraph->addEdge(current, next, min, true);                        // dodanie krawedzi do grafu koncowego
        current = next;                                                     // ustawienie nastepnego elementu
    }
    minGraph->addEdge(current, start, graph->getWeight(current, start), true);   // dodanie ostatniej krawedzi

    delete[] visited;
    return new ATSP(new Permutation(n, permTab), minGraph);
}

void ATSP::print() {
    if (!this) {
        printf("brak grafu\n");
        return;
    }

    printf("\nRowiazanie: %d\n", graph->getWeightsSum());
    printf("Permutacja wierzcholkow: ");
    permutation->printTab();
    printf("\n");
    graph->print();

}

int ATSP::Annealing() {
    auto n = graph->getPoints();
    for (auto i = 0; i < n; i++) {
        cities.push_back(i);
    }
    initT();
    run();
    return getTotalDistance(cities);
}

void ATSP::run() {
    auto best = cities;
    random_shuffle(cities.begin(), cities.end());
    auto i = 0;
    while (T > Tmin) {
        i++;
        next_step();
//        printf("%d: %.10f    %d    %d\n", i, T, getTotalDistance(cities), getTotalDistance(best));
//        if (i % 1000 == 0) {
//            printf("%d: %.10f    %d    %d\n", i, T, getTotalDistance(), getTotalDistance(best));
//        }
        if (getTotalDistance(cities) < getTotalDistance(best)) {
//            puts("zmieniono");
            best = cities;
        }
    }
    cities = best;
}

void ATSP::next_step() {
    auto dim = (int) cities.size();
    for (auto i = 0; i < dim * dim / 4; i++) {
        auto temp = cities;
        swap(temp[randrange()], temp[randrange()]);
        auto diff = getTotalDistance(temp) - getTotalDistance(cities);
        if (diff <= 0) {
            cities.swap(temp);
        } else if (random() < P(temp)) {
            cities.swap(temp);
        }
    }
    T = G();
}

double ATSP::P(vector<int> &c) const {
    return exp((getTotalDistance(cities) - getTotalDistance(c)) / T);
}

double ATSP::G() const {
    return T * alpha;
}

int ATSP::randrange() const {
    return (int) (rand() % cities.size());
}

double ATSP::random() const {
    return double(rand() % 100) / 100;
}

int ATSP::getDistance(int c1, int c2) const {
    return graph->getWeight(c1, c2);
}

int ATSP::getTotalDistance(vector<int> vec) const {
    int total = getDistance(vec.back(), vec.front());
//    cout << "len of vec " << vec.size() << endl;
//    int total = graph->getWeight(vec.back(), vec.front())
//    int total = 0;
    for (auto it = vec.begin() + 1; it != vec.end(); it++) {
        total += getDistance(*(it - 1), *it);
    }
    return total;
}

void ATSP::initT() {
    vector<int> v;
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

ATSP::ATSP(Graph *g) : graph(g) {}
