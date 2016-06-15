/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Statements.hpp"
#include "Expressions.hpp"

using namespace AST;

ReturnStmt::ReturnStmt(ASTPtr<Expression> value) : value(value) {
}

void ReturnStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> ReturnStmt::getValue() {
    return value;
}


VariableDefStmt::VariableDefStmt(std::string name, ASTPtr<TypeStmt> typeStmt)
    : name(name), typeStmt(typeStmt) {
}

void VariableDefStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string VariableDefStmt::getName() {
    return name;
}

ASTPtr<TypeStmt> VariableDefStmt::getTypeStmt() {
    return typeStmt;
}

llvm::AllocaInst* VariableDefStmt::getAllocaInst() {
    return allocaInst;
}

void VariableDefStmt::setAllocaInst(llvm::AllocaInst* allocaInst) {
    this->allocaInst = allocaInst;
}


VariableDefAssignStmt::VariableDefAssignStmt(std::string name,
    ASTPtr<TypeStmt> type, ASTPtr<Expression> value)
    : VariableDefStmt(name, type), value(value) {
}

void VariableDefAssignStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> VariableDefAssignStmt::getValue() {
    return value;
}
