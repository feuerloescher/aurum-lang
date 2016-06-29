/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Statements.hpp"
#include "ASTPass.hpp"

using namespace AST;

Statement::Statement(CodeLocation codeLocation) : codeLocation(codeLocation) {
}


ReturnStmt::ReturnStmt(ASTPtr<Expression> value, CodeLocation codeLocation)
    : Statement(codeLocation), value(value) {
}

void ReturnStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> ReturnStmt::getValue() {
    return value;
}


VariableDefStmt::VariableDefStmt(ASTPtr<TypeStmt> typeStmt, std::string name,
    CodeLocation codeLocation)
    : Statement(codeLocation), typeStmt(typeStmt), name(name),
    allocaInst(nullptr) {
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


VariableDefAssignStmt::VariableDefAssignStmt(ASTPtr<TypeStmt> type,
    std::string name, ASTPtr<Expression> value, CodeLocation codeLocation)
    : VariableDefStmt(type, name, codeLocation), value(value) {
}

void VariableDefAssignStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> VariableDefAssignStmt::getValue() {
    return value;
}
