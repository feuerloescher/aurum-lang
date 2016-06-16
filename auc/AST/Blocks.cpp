/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Blocks.hpp"

using namespace AST;

Block::Block() : parentBlock(nullptr), llvmBlock(nullptr) {
}

void Block::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

StatementList& Block::getStatements() {
    return statements;
}

void Block::push_back(ASTPtr<Statement> statement) {
    statements.push_back(statement);
}

ASTMap<VariableDefStmt*>& Block::getVariables() {
    return variables;
}

Block* Block::getParentBlock() {
    return parentBlock;
}

void Block::setParentBlock(Block* block) {
    parentBlock = block;
}

llvm::BasicBlock* Block::getLLVMBlock() {
    return llvmBlock;
}

void Block::setLLVMBlock(llvm::BasicBlock* llvmBlock) {
    this->llvmBlock = llvmBlock;
}


ASTPtr<Expression> IfStmt::getCondition() {
    return condition;
}

Block& IfStmt::getBody() {
    return body;
}

void IfStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> WhileLoop::getCondition() {
    return condition;
}

Block& WhileLoop::getBody() {
    return body;
}

void WhileLoop::runPass(ASTPass& pass) {
    pass.runOn(*this);
}
