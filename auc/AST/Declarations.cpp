/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Declarations.hpp"

#include <sstream>

using namespace AST;

FunctionDef::FunctionDef(std::string name, ASTPtr<Type> type)
    : name(name), type(type) {
}

void FunctionDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionDef::getName() {
    return name;
}

ASTPtr<Type> FunctionDef::getType() {
    return type;
}

VariableDefStmtList& FunctionDef::getParameters() {
    return parameters;
}

Block& FunctionDef::getBody() {
    return body;
}
