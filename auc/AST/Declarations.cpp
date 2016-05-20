/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Declarations.hpp"

#include <sstream>

using namespace AST;

FunctionDecl::FunctionDecl(std::string name, ASTPtr<Type> type)
    : name(name), type(type) {
}

void FunctionDecl::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionDecl::getName() {
    return name;
}

ASTPtr<Type> FunctionDecl::getType() {
    return type;
}

VariableDefStmtList& FunctionDecl::getParameters() {
    return parameters;
}

StatementList& FunctionDecl::getBody() {
    return body;
}
