#include "sanitize.hpp"

void regexReplace(std::string* str, const Replace* replace, const size_t size) {
    std::regex reg;

    for (size_t i = 0; i < size; i++) {
        reg = std::regex(replace[i].oldText);
        *str = std::regex_replace(*str, reg, replace[i].newText);
    }
}

std::string extractVars(std::string str) {
    std::regex reg;
    for (size_t i = 0; i < latexSize; i++) {
        reg = std::regex(latexReplace[i].oldText);
        str = std::regex_replace(str, reg, "");
    }

    std::string ret = "";
    for (int i = 0; i < str.size(); i++) {
        if (std::find(ret.begin(), ret.end(), str[i]) == ret.end()) {
            ret.push_back(str[i]);
        }
    }

    reg = std::regex("[^a-zA-Z]");
    ret = std::regex_replace(ret, reg, "");

    return ret;
}

void sanitize(std::string* latex) {
    regexReplace(latex, latexReplace, latexSize);
}

void latex(std::string* cparse) {
    regexReplace(cparse, expReplace, expSize);
}