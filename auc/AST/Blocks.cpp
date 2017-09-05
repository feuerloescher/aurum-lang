/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Blocks.hpp"
#include "Passes/ASTPass.hpp"

using namespace AST;

Block::Block(CodeLocation codeLocation)
        : Statement(codeLocation) {
    /// \todo Add a getName() method to Blocks,
    /// for context in error messages
}

void Block::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

StatementList& Block::getStatements() {
    return statements;
}

void Block::push_back(StatementPtr statement) {
    statements.push_back(statement);
}

ASTMap<VariableDefStmt*>& Block::getVariables() {
    return variables;
}


IfStmt::IfStmt(ExpressionPtr condition, BlockPtr body, CodeLocation codeLocation)
        : Statement(codeLocation), condition(condition), body(body) {
}

ExpressionPtr IfStmt::getCondition() {
    return condition;
}

BlockPtr& IfStmt::getBody() {
    return body;
}

void IfStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ExpressionPtr WhileLoop::getCondition() {
    return condition;
}

Block& WhileLoop::getBody() {
    return body;
}

void WhileLoop::runPass(ASTPass& pass) {
    pass.runOn(*this);
}
