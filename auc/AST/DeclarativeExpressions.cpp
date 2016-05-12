/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "DeclarativeExpressions.hpp"

#include <sstream>

using namespace AST;

std::string FunctionDeclExpr::toString() {
    std::ostringstream str;
    str << "FunctionDeclExpr(Name: " << name << "; Body: "
        << ImpListToString(body) << ")";
    return str.str();
}

std::string AST::DeclListToString(DeclarativeExprList list) {
    std::ostringstream str;
    str << "DeclarativeExprList {\n";
    for (ASTPtr<DeclarativeExpr> expression : list) {
        str << expression->toString() << "\n\n";
    }
    str << "}";
    return str.str();
}
