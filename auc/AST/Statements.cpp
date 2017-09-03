/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Statements.hpp"
#include "ASTPass.hpp"

using namespace AST;

Statement::Statement(Block* parentBlock, CodeLocation codeLocation)
    : ASTElement(codeLocation), parentBlock(parentBlock) {
}

Block* Statement::getParentBlock() {
    return parentBlock;
}


ReturnStmt::ReturnStmt(ASTPtr<Expression> value, Block* parentBlock,
    CodeLocation codeLocation)
    : Statement(parentBlock, codeLocation), value(value) {
}

void ReturnStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> ReturnStmt::getValue() {
    return value;
}


VariableDefStmt::VariableDefStmt(ASTPtr<TypeStmt> typeStmt, std::string name,
    Block* parentBlock, CodeLocation codeLocation)
    : Statement(parentBlock, codeLocation), typeStmt(typeStmt), name(name) {
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


VariableDefAssignStmt::VariableDefAssignStmt(ASTPtr<TypeStmt> type,
    std::string name, ASTPtr<Expression> value, Block* parentBlock,
    CodeLocation codeLocation)
    : VariableDefStmt(type, name, parentBlock, codeLocation), value(value) {
}

void VariableDefAssignStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> VariableDefAssignStmt::getValue() {
    return value;
}
