/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ImperativeExpressions.hpp"
#include "ValueExpressions.hpp"

#include <sstream>

using namespace AST;

ReturnExpr::ReturnExpr(ASTPtr<ValueExpr> value) : value(value) {
}

void ReturnExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<ValueExpr> ReturnExpr::getValue() {
    return value;
}


VariableDefExpr::VariableDefExpr(std::string name, ASTPtr<TypeExpr> type)
    : name(name), type(type) {
}

void VariableDefExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string VariableDefExpr::getName() {
    return name;
}

ASTPtr<TypeExpr> VariableDefExpr::getType() {
    return type;
}


VariableDefAssignExpr::VariableDefAssignExpr(std::string name,
    ASTPtr<TypeExpr> type, ASTPtr<ValueExpr> value)
    : name(name), type(type), value(value) {
}

void VariableDefAssignExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string VariableDefAssignExpr::getName() {
    return name;
}

ASTPtr<TypeExpr> VariableDefAssignExpr::getType() {
    return type;
}

ASTPtr<ValueExpr> VariableDefAssignExpr::getValue() {
    return value;
}
