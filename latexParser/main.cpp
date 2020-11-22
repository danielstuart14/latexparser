#include <string>
#include "cparse.hpp"
#include "sanitize.hpp"
#include "solver.hpp"

std::string truthTable(std::string);

#ifdef EMSCRIPTEN
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
    function("truthTable", &truthTable);
}
#else
#include <iostream>

int main() {
    std::string s;
    std::getline(std::cin, s);

    std::cout << truthTable(s);

    return 0;
}
#endif

std::string truthTable(std::string input) {
    static bool startup = false;
    if (!startup) {
        cparseStartup();
        startup = true;
    }

    sanitize(&input);

    std::string variables = extractVars(input);
    return logicSolver(input, variables);
}