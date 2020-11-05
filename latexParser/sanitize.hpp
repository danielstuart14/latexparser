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
    Replace{"<->", " <=> "},
    Replace{"iff", " <=> "},
    Replace{"\\\\rightarrow", " -> "}, //must be after \left\to\rightarrow
    Replace{"->", " -> "}, //must be after <->
    Replace{"implies", " -> "},
    Replace{"&&", " && "},
    Replace{"and", " && "},
    Replace{"\\^", " && "},
    Replace{"\\\\wedge", " && "},
    Replace{"xor", " ^ "}, //must be after \^
    Replace{"!", " !"},
    Replace{"\\\\lnot", " !"},
    Replace{"not", " !"}, //must be after \lnot
    Replace{"\\¬", " !"},
    Replace{"\\\\neg", " !"},
    Replace{"\\|\\|", " || "},
    Replace{"or", " || "},
    Replace{"\\\\vee", " || "},
    Replace{"v", " || "} //must be after vee
};

const size_t latexSize = sizeof(latexReplace) / sizeof(Replace);

void sanitize(std::string*);

#endif