/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "IdentifierPass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Expressions.hpp"
#include "AST/Errors.hpp"
#include "AST/Type.hpp"

using namespace AST;
using namespace Passes;

IdentifierPass::IdentifierPass(AbstractSyntaxTree& ast)
    : ASTPass(ast), currentBlock(nullptr) {
}

void IdentifierPass::run() {
    ast.getFunctionDefs().clear();
    currentBlock = nullptr;
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void IdentifierPass::runOn(FunctionDef& func) {
    if (!ast.getFunctionDefs().insert(func)) {
        throw ExistingIdentifierError(func.getName());
    }
    func.getTypeStmt()->runPass(*this);
    currentBlock = &func.getBody();
    for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
        innerStmt->runPass(*this);
    }
    func.getBody().runPass(*this);
}

void IdentifierPass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void IdentifierPass::runOn(VariableDefStmt& stmt) {
    if (!currentBlock->getVariables().insert(stmt)) {
        throw UnknownIdentifierError(stmt.getName());
    }
    stmt.getTypeStmt()->runPass(*this);
}

void IdentifierPass::runOn(VariableDefAssignStmt& stmt) {
    if (!currentBlock->getVariables().insert(stmt)) {
        throw UnknownIdentifierError(stmt.getName());
    }
    stmt.getTypeStmt()->runPass(*this);
    stmt.getValue()->runPass(*this);
}

void IdentifierPass::runOn(Block& stmt) {
    if (currentBlock != &stmt) {
        stmt.setParentBlock(currentBlock);
        currentBlock = &stmt;
    }
    for (ASTPtr<Statement> innerStmt : stmt.getStatements()) {
        innerStmt->runPass(*this);
    }
    currentBlock = stmt.getParentBlock();
}

void IdentifierPass::runOn(IfStmt& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void IdentifierPass::runOn(WhileLoop& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void IdentifierPass::runOn(TypeStmt& stmt) {
    Type* type = ast.getTypes().find(stmt.getName());
    if (!type) {
        throw UnknownIdentifierError(stmt.getName());
    }
    stmt.setType(type);
}

void IdentifierPass::runOn(FunctionCallExpr& stmt) {
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        expr->runPass(*this);
    }
}

void IdentifierPass::runOn(ConstUInt32Expr& stmt) {
}

void IdentifierPass::runOn(VariableExpr& stmt) {
    /// \todo Copy variables from parent blocks in runOn(Block),
    /// or search through parent blocks here
    VariableDefStmt* variableDef = currentBlock->getVariables().find(
        stmt.getName());
    if (!variableDef) {
        throw UnknownIdentifierError(stmt.getName());
    }
    stmt.setVariableDefStmt(variableDef);
}

void IdentifierPass::runOn(UnaryOpExpr& stmt) {
    stmt.getOperand()->runPass(*this);
}

void IdentifierPass::runOn(BinaryOpExpr& stmt) {
    stmt.getOperand1()->runPass(*this);
    stmt.getOperand2()->runPass(*this);
}

void IdentifierPass::runOn(UnaryAssignOpExpr& stmt) {
    stmt.getVariable()->runPass(*this);
}

void IdentifierPass::runOn(BinaryAssignOpExpr& stmt) {
    stmt.getVariable()->runPass(*this);
    stmt.getOperand()->runPass(*this);
}
