//
// Created by matbur on 08.10.16.
//

#include "File.h"

File::File(const string &fileName) {
    ifstream file(fileName.c_str());
    string line, fieldName, field;
    string delimiter = ":";
    while (getline(file, line)) {
        fieldName = line.substr(0, line.find(delimiter));
        fieldName = trim(fieldName);
        field = line.substr(line.find(delimiter) + 1, line.length());
        field = trim(field);
        if (fieldName == "NAME") {
            name = field;
        } else if (fieldName == "COMMENT") {
            comment = field;
        } else if (fieldName == "TYPE") {
            type = field;
        } else if (fieldName == "DIMENSION") {
            dimension = atoi(field.c_str());
        } else if (fieldName == "EDGE_WEIGHT_TYPE") {
            edge_weight_type = field;
        } else if (fieldName == "NODE_COORD_SECTION") {
            node_coord_section = new string[dimension];
            for (auto i = 0; i < dimension; i++) {
                getline(file, line);
                node_coord_section[i] = line;
            }
        } else {
            cout << line << endl;
        }
    }
    file.close();
}

string File::toString() {
    return "name: " + name +
           "\ncomment: " + comment +
           "\ntype: " + type +
           "\ndimension: " + int2string(dimension) +
           "\nedge_weight_type: " + edge_weight_type;
}

string File::int2string(int n) {
    stringstream ss;
    string s;
    ss << n;
    ss >> s;
    return s;
}
