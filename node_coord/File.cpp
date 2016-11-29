//
// Created by matbur on 08.10.16.
//

#include "File.h"

File::File(const string &fileName) {
    if (!loadFile(fileName)) {
        puts("Error with file");
        exit(1);
    }
}

bool File::loadFile(const string &fileName) {
    ifstream file(fileName.c_str());

    if (!file.good()) {
        return false;
    }

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
            for (auto i = 0; i < dimension; i++) {
                getline(file, line);
                node_coord_section.push_back(line);
            }
        } else if (fieldName == "EOF") {
            break;
        } else {
            cout << "fieldName: " << fieldName << endl;
        }
    }
    file.close();
    return true;
}

