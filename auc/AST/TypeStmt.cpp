/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "TypeStmt.hpp"
#include "ASTPass.hpp"

using namespace AST;

TypeStmt::TypeStmt(std::string name, CodeLocation codeLocation)
    : ASTElement(codeLocation), name(name), type(nullptr) {
}

void TypeStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string TypeStmt::getName() {
    return name;
}

ASTPtr<Type> TypeStmt::getType() {
    return type;
}

void TypeStmt::setType(ASTPtr<Type> type) {
    this->type = type;
}
