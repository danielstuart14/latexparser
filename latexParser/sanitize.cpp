#include "sanitize.hpp"

void regexReplace(std::string* str, const Replace* replace, const size_t size) {
    std::regex reg;

    for (size_t i = 0; i < size; i++) {
        reg = std::regex(replace[i].oldText);
        *str = std::regex_replace(*str, reg, replace[i].newText);
    }
}

void sanitize(std::string* latex) {
    regexReplace(latex, latexReplace, latexSize);
}

void latex(std::string* cparse) {
    regexReplace(cparse, expReplace, expSize);
}