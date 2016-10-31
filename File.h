//
// Created by matbur on 08.10.16.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

class File {
public:
    string
            type,
            name,
            comment,
            edge_weight_type;
    int dimension;
    vector<string> node_coord_section;

    File(const string &fileName);

    bool loadFile(const string &fileName);
};

// trim from start
static inline string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}