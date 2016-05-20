/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Statements.hpp"
#include "Expressions.hpp"

#include <sstream>

using namespace AST;

ReturnStmt::ReturnStmt(ASTPtr<Expression> value) : value(value) {
}

void ReturnStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> ReturnStmt::getValue() {
    return value;
}


VariableDefStmt::VariableDefStmt(std::string name, ASTPtr<Type> type)
    : name(name), type(type) {
}

void VariableDefStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string VariableDefStmt::getName() {
    return name;
}

ASTPtr<Type> VariableDefStmt::getType() {
    return type;
}


VariableDefAssignStmt::VariableDefAssignStmt(std::string name,
    ASTPtr<Type> type, ASTPtr<Expression> value)
    : VariableDefStmt(name, type), value(value) {
}

void VariableDefAssignStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> VariableDefAssignStmt::getValue() {
    return value;
}
