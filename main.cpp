#include <iostream>

#include "File.h"

int main() {
    auto f = new File("data/a280.tsp");
    cout << f->toString() << endl;
    return 0;
}