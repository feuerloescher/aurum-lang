/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "TypePass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Expressions.hpp"
#include "AST/Errors.hpp"
#include "AST/Type.hpp"
#include "AST/ScalarTypes.hpp"

using namespace AST;
using namespace Passes;

TypePass::TypePass(AbstractSyntaxTree& ast)
    : ASTPass(ast) {
}

void TypePass::run() {
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void TypePass::runOn(FunctionDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
        innerStmt->runPass(*this);
    }
    func.getBody().runPass(*this);
}

void TypePass::runOn(MethodDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    func.getObjectTypeStmt()->runPass(*this);
    for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
        innerStmt->runPass(*this);
    }
    func.getBody().runPass(*this);
}

void TypePass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void TypePass::runOn(VariableDefStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
}

void TypePass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stmt.getValue()->runPass(*this);
}

void TypePass::runOn(Block& stmt) {
    for (ASTPtr<Statement> innerStmt : stmt.getStatements()) {
        innerStmt->runPass(*this);
    }
}

void TypePass::runOn(IfStmt& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void TypePass::runOn(WhileLoop& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void TypePass::runOn(TypeStmt& stmt) {
}

void TypePass::runOn(FunctionCallExpr& stmt) {
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        expr->runPass(*this);
    }
}

void TypePass::runOn(MethodCallExpr& stmt) {
    stmt.getObjectExpr()->runPass(*this);
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        expr->runPass(*this);
    }
    /// Resolve method identifier (type of stmt.getObjectExpr() is resolved now)
    MethodDef* methodDef =
        stmt.getObjectExpr()->getType()->getMethodDefs().find(stmt.getName());
    if (!methodDef) {
        throw UnknownIdentifierError(stmt.getName());
    }
    stmt.setMethodDef(methodDef);
}

void TypePass::runOn(ConstUInt32Expr& stmt) {
    /// \todo Find scalar types more elegantly, e.g. store them directly in AST
    ASTPtr<Type> type = ast.getTypes().find("uint32");
    if (!type) {
        throw UnknownIdentifierError("uint32");
    }
    stmt.setType(type);
}

void TypePass::runOn(VariableExpr& stmt) {
    stmt.setType(stmt.getVariableDefStmt()->getTypeStmt()->getType());
}
