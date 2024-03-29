#include "Graph.h"


Graph::Graph() : points(0), weights(nullptr) {}

Graph::Graph(int points) : points(points) {
    init();
}

Graph::Graph(const Graph &graph) : Graph() {
    if (this == &graph) return;

    points = graph.points;
    init();

    for (auto r = 0; r < points; r++)
        memcpy(weights[r], graph.weights[r], sizeof(int) * points);
}

Graph &Graph::operator=(const Graph &graph) {
    if (this == &graph) return *this;

    reset(graph.points);

    for (auto r = 0; r < points; r++)
        memcpy(weights[r], graph.weights[r], sizeof(int) * points);

    return *this;
}

bool Graph::operator<(const Graph &graph) {
    return getWeightsSum() < graph.getWeightsSum();
}

Graph::~Graph() {
    clear();
}

void Graph::reset(int points) {
    clear();
    this->points = points;
    init();
}

void Graph::init() {
    weights = new int *[points];

    for (auto i = 0; i < points; i++)
        weights[i] = new int[points];

    for (auto r = 0; r < points; r++)
        memset(weights[r], -1, sizeof(int) * points);
}

bool Graph::addEdge(int from, int to, int weight, bool oneway /*= false*/) {
    if (!pointExists(from) || !pointExists(to) || from == to)
        return false;

    bool added = weights[from][to] == -1;

    if (added)
        weights[from][to] = weight;

    if (oneway)
        return added;

    added = weights[to][from] == -1;

    if (added)
        weights[to][from] = weight;

    return added;
}

void Graph::clear() {
    for (auto i = 0; i < points; i++)
        delete[] weights[i];

    delete[] weights;
    weights = nullptr;
    points = 0;
}

int Graph::getPoints() const {
    return points;
}

bool Graph::pointExists(int point) const {
    return point >= 0 && point < points;
}

int Graph::getWeightsSum() const {
    int sum = 0, temp;
    for (auto r = 0; r < points; r++)
        for (auto c = 0; c < points; c++) {
            temp = weights[r][c];
            if (temp != -1)
                sum += temp;
        }
    if (sum == 0)
        sum = INT_MAX;
    return sum;
}

void Graph::print() const {
    printf("Points in graph: %d\n", points);
    puts("Neighbours:");

    printf("  W ");
    for (auto i = 0; i < points; i++)
        printf("%3d ", i);
    putchar('\n');

    int temp;
    for (auto r = 0; r < points; r++) {
        printf("%3d ", r);
        for (auto c = 0; c < points; c++) {
            temp = weights[r][c];
            if (temp != -1)
                printf("%3d ", temp);
            else
                printf("    ");
        }
        putchar('\n');
    }
}

void Graph::generate(int points, bool oneway /*= false*/) {
    if (points < 2) return;                             // musi byc conajmniej jedna krawedz

    auto maxWeight = 100;                               // wagi z zakresu [1, 100]

    reset(points);                                      // wyzerowanie

    for (auto from = 0; from < points; from++) {
        for (auto to = 0; to < points; to++) {
            if (from == to)
                continue;

            addEdge(from, to, rand() % maxWeight + 1, oneway);
        }
    }
}

int Graph::getWeight(int row, int col) const {
    return weights[row][col];
}




// example use
/*
int main() {
    Graph graph(4);
    Graph x;

    printf("%d\n", x.getPoints());

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 6);
    graph.addEdge(2, 3, 10);

    graph.print();

    puts("own printing");
    for(int p=0; p < graph.getPoints(); p++) {
        for(auto e : graph.getNeighbours(p))
            printf("from %d to %d by weight %d\n", p, e.to, e.weight);

    }

    return 0;
}
*/

