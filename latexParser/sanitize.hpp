#ifndef PARSER_H
#define PARSER_H

#include <regex>
#include <string>

struct Replace {
    const char* oldText;
    const char* newText;
};

const Replace latexReplace[] = {
    Replace{" ", ""},
    Replace{"\\\\space", ""},
    Replace{"\\\\right", ""},
    Replace{"\\\\left", ""},
    Replace{"\\\\left\\\\to\\\\rightarrow", " <=> "},
    Replace{"\\\\leftrightarrow", " <=> "},
    Replace{"<->", " <=> "},
    Replace{"iff", " <=> "},
    Replace{"\\\\rightarrow", " -> "}, //must be after \left\to\rightarrow
    Replace{"\\\\to", " -> "},
    Replace{"->", " -> "}, //must be after <->
    Replace{"implies", " -> "},
    Replace{"&&", " && "},
    Replace{"and", " && "},
    Replace{"\\^", " && "},
    Replace{"\\\\wedge", " && "},
    Replace{"\\\\land", " && "},
    Replace{"\\\\oplus", " ^ "}, //must be after \^
    Replace{"xor", " ^ "}, //must be after \^
    Replace{"!", " !"},
    Replace{"\\\\lnot", " !"},
    Replace{"not", " !"}, //must be after \lnot
    Replace{"\\�", " !"},
    Replace{"\\\\neg", " !"},
    Replace{"\\|\\|", " || "},
    Replace{"or", " || "},
    Replace{"\\\\vee", " || "},
    Replace{"\\\\lor", " && "},
    Replace{"v", " || "} //must be after vee
};

const Replace latexExpression[] = {
    Replace{" <=> ","\\\\left\\\\to\\\\rightarrow"},
    Replace{" -> ","\\\\rightarrow"}, //must be after \left\to\rightarrow
    Replace{" && ","\\\\wedge"},
    Replace{" ^ ","\\\\oplus"}, //must be after \^
    Replace{" !","\\\\neg"},
    Replace{" || ","\\\\vee"},
};
const size_t latexSize = sizeof(latexReplace) / sizeof(Replace);
const size_t latexExpressionSize = sizeof(latexExpression) / sizeof(Replace);

void sanitize(std::string*);
void returnFormula(std::string*);

#endif