/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "BlockExpressions.hpp"

#include <sstream>

using namespace AST;

std::string IfExpr::toString() {
    std::ostringstream str;
    str << "IfExpr(Condition: " << condition->toString() << "; Body: "
        << ImpListToString(body) << ")";
    return str.str();
}

std::string WhileLoopExpr::toString() {
    std::ostringstream str;
    str << "WhileLoopExpr(Condition: " << condition->toString() << "; Body: "
        << ImpListToString(body) << ")";
    return str.str();
}
