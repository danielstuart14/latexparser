#include "sanitize.hpp"

void sanitize(std::string* latex) {
    std::regex reg;

    for (size_t i = 0; i < latexSize; i++) {
        reg = std::regex(latexReplace[i].oldText);
        *latex = std::regex_replace(*latex, reg, latexReplace[i].newText);
    }
}

void returnFormula(std::string* cparse) {
    std::regex reg;

    for (size_t i = 0; i < latexExpressionSize; i++) {
        reg = std::regex(latexExpression[i].oldText);
        *cparse = std::regex_replace(*cparse, reg, latexExpression[i].newText);
    }
}