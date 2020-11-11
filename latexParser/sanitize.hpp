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
    Replace{"\\\\", ""},
    Replace{"space", ""},
    Replace{"right", ""},
    Replace{"left", ""},
    Replace{"lefttorightarrow", " <=> "},
    Replace{"leftrightarrow", " <=> "},
    Replace{"<->", " <=> "},
    Replace{"iff", " <=> "},
    Replace{"rightarrow", " -> "}, //must be after \left\to\rightarrow
    Replace{"to", " -> "}, //must be after \left\to\rightarrow
    Replace{"->", " -> "}, //must be after <->
    Replace{"implies", " -> "},
    Replace{"&&", " && "},
    Replace{"land", " && "},
    Replace{"and", " && "}, //must be after land
    Replace{"\\^", " && "},
    Replace{"wedge", " && "},
    Replace{"oplus", " ^ "}, //must be after \^
    Replace{"xor", " ^ "}, //must be after \^
    Replace{"!", " !"},
    Replace{"lnot", " !"},
    Replace{"not", " !"}, //must be after lnot
    Replace{"\\¬", " !"},
    Replace{"neg", " !"},
    Replace{"\\|\\|", " || "},
    Replace{"lor", " || "},
    Replace{"or", " || "}, //must be after lor
    Replace{"vee", " || "},
    Replace{"v", " || "} //must be after vee
};

const Replace expReplace[] = {
    Replace{"<=>","\\iff"},
    Replace{"->","\\implies"},
    Replace{"&&","\\land"},
    Replace{"\\^","\\oplus"},
    Replace{"!","\\lnot"},
    Replace{"\\|\\|","\\lor"},
};
const size_t latexSize = sizeof(latexReplace) / sizeof(Replace);
const size_t expSize = sizeof(expReplace) / sizeof(Replace);

void sanitize(std::string*);
void latex(std::string*);

#endif