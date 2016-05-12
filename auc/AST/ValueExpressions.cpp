/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ValueExpressions.hpp"

#include <sstream>

using namespace AST;

ValueExpr::ValueExpr() {

}

std::string AST::ParamListToString(ValueExprList list) {
    std::ostringstream str;
    str << "ParamListToString(\n";
    for (ASTPtr<ValueExpr> expression : list) {
        str << expression->toString() << "; ";
    }
    str << ")";
    return str.str();
}

std::string FunctionCallExpr::toString() {
    std::ostringstream str;
    str << "FunctionCallExpr(Name: " << name << "; Parameters: "
        << ParamListToString(parameters) << ")";
    return str.str();
}

std::string ConstIntExpr::toString() {
    std::ostringstream str;
    str << "ConstIntExpr(Value: " << value << ")";
    return str.str();
}


VariableExpr::VariableExpr(std::string name) : name(name) {

}

std::string VariableExpr::toString() {
    std::ostringstream str;
    str << "VariableExpr(Name: " << name << ")";
    return str.str();
}


std::string UnaryOpExpr::toString() {
    std::ostringstream str;
    str << "UnaryOpExpr(Name: " << name << "; Operand: " << operand->toString()
        << ")";
    return str.str();
}

std::string BinaryOpExpr::toString() {
    std::ostringstream str;
    str << "BinaryOpExpr(Name: " << name << "; Operand1: "
        << operand1->toString() << "; Operand2: " << operand2->toString() << ")";
    return str.str();
}

std::string UnaryAssignOpExpr::toString() {
    std::ostringstream str;
    str << "UnaryAssignOpExpr(Variable: " << variable->toString() << "; Name: "
        << name << ")";
    return str.str();
}

std::string BinaryAssignOpExpr::toString() {
    std::ostringstream str;
    str << "BinaryAssignOpExpr(Variable: " << variable->toString() << "; Name: "
        << name << "; Operand: " << operand->toString() << ")";
    return str.str();
}
