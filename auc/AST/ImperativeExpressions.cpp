/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ImperativeExpressions.hpp"
#include "ValueExpressions.hpp"

#include <sstream>

using namespace AST;

ImperativeExpr::ImperativeExpr() {

}

std::string AST::ImpListToString(ImperativeExprList list) {
    std::ostringstream str;
    str << "ImperativeExprList {\n";
    for (ASTPtr<ImperativeExpr> expression : list) {
        str << expression->toString() << ";\n";
    }
    str << "}";
    return str.str();
}

std::string ReturnExpr::toString() {
    std::ostringstream str;
    str << "ReturnExpr(Value: " << value << ")";
    return str.str();
}

std::string VariableDefExpr::toString() {
    std::ostringstream str;
    str << "VariableDefExpr(Name: " << name << "; TypeExpr: " << type->toString()
        << ")";
    return str.str();
}

std::string VariableDefAssignExpr::toString() {
    std::ostringstream str;
    str << "VariableDefAssignExpr(Name: " << name << "; TypeExpr: "
        << type->toString() << "; Value: " << value->toString() << ")";
    return str.str();
}
