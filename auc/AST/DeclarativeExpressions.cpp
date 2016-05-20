/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "DeclarativeExpressions.hpp"

#include <sstream>

using namespace AST;

FunctionDeclExpr::FunctionDeclExpr(std::string name, ASTPtr<TypeExpr> type)
    : name(name), type(type) {
}

void FunctionDeclExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionDeclExpr::getName() {
    return name;
}

ASTPtr<TypeExpr> FunctionDeclExpr::getType() {
    return type;
}

VariableDefExprList& FunctionDeclExpr::getParameters() {
    return parameters;
}

ImperativeExprList& FunctionDeclExpr::getBody() {
    return body;
}
