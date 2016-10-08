//
// Created by matbur on 08.10.16.
//

#include "City.h"

City::City(string data) {
    init(data);
}

void City::init(string data) {
    stringstream ss;
    ss << data;
    ss >> index >> x >> y;
}

void City::print() const {
    printf("%d: (%d, %d)", index, x, y);
}

