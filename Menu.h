#pragma once

#include "Graph.h"
#include "FileSupport.h"
#include "ATSP.h"

class Menu {
private:
    static void printError(int er);

    static void tspMenu();

    static int tspGenerate(Graph *data);

public:
    static void init();
};

