#ifndef CPARSE_H
#define CPARSE_H

#include "./cparse/shunting-yard.h"
#include "./cparse/shunting-yard-exceptions.h"

packToken impliesOp(const packToken& left, const packToken& right,
    evaluationData* data) {
    return left.asBool() <= right.asBool();
}

packToken iffOp(const packToken& left, const packToken& right,
    evaluationData* data) {
    return left.asBool() == right.asBool();
}

packToken andOp(const packToken& left, const packToken& right,
    evaluationData* data) {
    return left.asBool() && right.asBool();
}

packToken orOp(const packToken& left, const packToken& right,
    evaluationData* data) {
    return left.asBool() || right.asBool();
}

packToken notOp(const packToken& left, const packToken& right,
    evaluationData* data) {
    return !right.asBool();
}

packToken xorOp(const packToken& left, const packToken& right,
    evaluationData* data) {
    return !left.asBool() != !right.asBool();
}

struct cparseStartup {
    cparseStartup() {
        OppMap_t& opp = calculator::Default().opPrecedence;

        opp.add("()", 1);
        opp.addUnary("!", 2);
        opp.add("&&", 3);
        opp.add("||", 4);
        opp.add("^", 5);
        opp.add("->", 6);
        opp.add("<=>", 7);

        opMap_t& opMap = calculator::Default().opMap;
        opMap.add({ UNARY, "!", NUM }, &notOp);
        opMap.add({ NUM, "&&", NUM }, &andOp);
        opMap.add({ NUM, "||", NUM }, &orOp);
        opMap.add({ NUM, "^", NUM }, &xorOp);
        opMap.add({ NUM, "->", NUM }, &impliesOp);
        opMap.add({ NUM, "<=>", NUM }, &iffOp);
    }
};
#endif