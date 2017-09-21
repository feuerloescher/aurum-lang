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
#include "Types/Type.hpp"
#include "Types/ScalarTypes.hpp"

using namespace AST;
using namespace Passes;

TypePass::TypePass(AbstractSyntaxTree& ast)
        : ASTPass(ast) {
}

void TypePass::run() {
    for (DeclarationPtr decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void TypePass::runOn(AST::FunctionDecl& funcDecl) {
    funcDecl.getReturnTypeStmt()->runPass(*this);
    for (VariableDefStmtPtr innerStmt : funcDecl.getParameters()) {
        innerStmt->runPass(*this);
    }
}

void TypePass::runOn(FunctionDef& func) {
    func.getFunctionDecl()->runPass(*this);
    func.getBody()->runPass(*this);
}

void TypePass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void TypePass::runOn(VariableDefStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    if (stmt.getTypeStmt()->getIsReference()) {
        throw ReferenceInitializationError(stmt.getCodeLocation());
    }
}

void TypePass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stmt.getValue()->runPass(*this);
}

void TypePass::runOn(Block& stmt) {
    for (StatementPtr innerStmt : stmt.getStatements()) {
        innerStmt->runPass(*this);
    }
}

void TypePass::runOn(IfStmt& stmt) {
    stmt.getCondition()->runPass(*this);
    if (stmt.getCondition()->getType() != ast.getTypes().find("bool")) {
        /// \todo Add search for implicit cast method
        throw ConditionTypeError(stmt.getCondition()->getCodeLocation(), stmt.getCondition()->getType());
    }
    stmt.getBody()->runPass(*this);
}

void TypePass::runOn(WhileLoop& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void TypePass::runOn(BasicTypeStmt& stmt) {
}

void TypePass::runOn(FunctionCallExpr& stmt) {
    for (ExpressionPtr expr : stmt.getArgs()) {
        expr->runPass(*this);
    }

    /// Check argument types
    auto paramIter = stmt.getFunctionDecl()->getParameters().begin();
    unsigned int argCounter = 0;
    for (ExpressionPtr arg : stmt.getArgs()) {
        argCounter++;
        if ((*paramIter)->getTypeStmt()->getType() != arg->getType()) {
            /// \todo Add search for implicit cast method
            throw ArgumentTypeError(arg->getCodeLocation(), stmt.getName(), argCounter,
                    (*paramIter)->getTypeStmt()->getType(), arg->getType());
        }
        if ((*paramIter)->getTypeStmt()->getIsReference() &&
                !(arg->getIsReference() || arg->getIsReferenceable())) {
            throw ArgumentReferenceError(arg->getCodeLocation(), stmt.getName(), argCounter, (*paramIter)->getName());
        }
        ++paramIter;
    }
}

void TypePass::runOn(ConstIntExpr& stmt) {
    stmt.getTypeStmt()->runPass(*this);
}

void TypePass::runOn(VariableExpr& stmt) {
    // nothing to do
}
