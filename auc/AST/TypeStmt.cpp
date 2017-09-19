/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "TypeStmt.hpp"
#include "Passes/ASTPass.hpp"

using namespace AST;
using namespace type;

TypeStmt::TypeStmt(CodeLocation codeLocation)
        : ASTElement(codeLocation), type(nullptr), isReference(false) {
}

TypePtr TypeStmt::getType() {
    return type;
}

void TypeStmt::setType(TypePtr type) {
    this->type = type;
}

bool TypeStmt::getIsReference() {
    return isReference;
}

void TypeStmt::setIsReference(bool isReference) {
    this->isReference = isReference;
}


BasicTypeStmt::BasicTypeStmt(std::string name, CodeLocation codeLocation)
        : TypeStmt(codeLocation), name(name) {
}

void BasicTypeStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string BasicTypeStmt::getName() {
    return name;
}
