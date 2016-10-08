//
// Created by matbur on 08.10.16.
//

#pragma once

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class City {
public:
    int index, x, y;

    City(string data);

    void init(string data);

    void print() const;
};
