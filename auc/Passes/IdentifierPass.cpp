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
#include "AST/Type.hpp"
#include "AST/Expressions.hpp"

using namespace AST;
using namespace Passes;

IdentifierPass::IdentifierPass(AbstractSyntaxTree& ast) : ASTPass(ast) {
}

void IdentifierPass::run() {
    ast.getFunctionDecls().clear();
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void IdentifierPass::runOn(FunctionDecl& decl) {
    if (!ast.getFunctionDecls().insert(decl)) {
        throw std::runtime_error("Function name " + decl.getName()
            + " already exists in this compilation unit.");
    }
    for (ASTPtr<VariableDefStmt> innerStmt : decl.getParameters()) {
        innerStmt->runPass(*this);
    }
    for (ASTPtr<Statement> innerStmt : decl.getBody()) {
        innerStmt->runPass(*this);
    }
}

void IdentifierPass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void IdentifierPass::runOn(VariableDefStmt& stmt) {
}

void IdentifierPass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void IdentifierPass::runOn(IfStmt& stmt) {
    for (ASTPtr<Statement> innerStmt : stmt.getBody()) {
        innerStmt->runPass(*this);
    }
}

void IdentifierPass::runOn(WhileLoop& stmt) {
    for (ASTPtr<Statement> innerStmt : stmt.getBody()) {
        innerStmt->runPass(*this);
    }
}

void IdentifierPass::runOn(FunctionCallExpr& stmt) {
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        expr->runPass(*this);
    }
}

void IdentifierPass::runOn(ConstIntExpr& stmt) {
}

void IdentifierPass::runOn(VariableExpr& stmt) {
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
