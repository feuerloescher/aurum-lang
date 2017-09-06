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
    for (ASTElementPtr decl : ast.getASTElements()) {
        decl->runPass(*this);
    }
}

void TypePass::runOn(FunctionDef& func) {
    func.getFunctionDecl()->getReturnTypeStmt()->runPass(*this);
    for (VariableDefStmtPtr innerStmt : func.getFunctionDecl()->getParameters()) {
        innerStmt->runPass(*this);
    }
    func.getBody()->runPass(*this);
}

void TypePass::runOn(MethodDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    func.getObjectTypeStmt()->runPass(*this);
    for (VariableDefStmtPtr innerStmt : func.getParameters()) {
        innerStmt->runPass(*this);
    }
    func.getBody()->runPass(*this);
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
    for (StatementPtr innerStmt : stmt.getStatements()) {
        innerStmt->runPass(*this);
    }
}

void TypePass::runOn(IfStmt& stmt) {
    stmt.getCondition()->runPass(*this);
    if (stmt.getCondition()->getType() != ast.getTypes().find("bool")) {
        /// \todo Add search for implicit cast method
        throw ConditionTypeError(stmt.getCondition()->getType());
    }
    stmt.getBody()->runPass(*this);
}

void TypePass::runOn(WhileLoop& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void TypePass::runOn(TypeStmt& stmt) {
}

void TypePass::runOn(FunctionCallExpr& stmt) {
    for (ExpressionPtr expr : stmt.getArgs()) {
        expr->runPass(*this);
    }

    /// Check argument types
    auto paramIter = stmt.getFunctionDef()->getFunctionDecl()->getParameters().begin();
    unsigned int argCounter = 0;
    for (ExpressionPtr arg : stmt.getArgs()) {
        argCounter++;
        if ((*paramIter)->getTypeStmt()->getType() != arg->getType()) {
            /// \todo Add search for implicit cast method
            throw ArgumentTypeError(stmt.getName(), argCounter,
                (*paramIter)->getTypeStmt()->getType(), arg->getType());
        }
    }
    stmt.setType(stmt.getFunctionDef()->getFunctionDecl()->getReturnTypeStmt()->getType());
    /// \todo Merge common code of FunctionCallExpr and MethodCallExpr handling
}

void TypePass::runOn(MethodCallExpr& stmt) {
    stmt.getObjectExpr()->runPass(*this);
    for (ExpressionPtr expr : stmt.getArgs()) {
        expr->runPass(*this);
    }
    /// Resolve method identifier (type of stmt.getObjectExpr() is resolved now)
    std::string mangledName = stmt.getMangledName();
    MethodDef* methodDef = stmt.getObjectExpr()->getType()->getMethodDefs().find(mangledName);
    if (!methodDef) {
        throw UnknownIdentifierError(mangledName);
    }
    if (stmt.getArgs().size() != methodDef->getParameters().size() - 1) {
        throw ArgumentCountError(stmt.getMangledName(),
            methodDef->getParameters().size() - 1, stmt.getArgs().size());
    }
    stmt.setMethodDef(methodDef);

    /// Check argument types
    auto paramIter = stmt.getMethodDef()->getParameters().begin();
    unsigned int argCounter = 0;
    for (ExpressionPtr arg : stmt.getArgs()) {
        argCounter++;
        if ((*paramIter)->getTypeStmt()->getType() != arg->getType()) {
            /// \todo Add search for implicit cast method
            throw ArgumentTypeError(stmt.getMangledName(), argCounter,
                (*paramIter)->getTypeStmt()->getType(), arg->getType());
        }
    }
    stmt.setType(stmt.getMethodDef()->getReturnTypeStmt()->getType());
}

void TypePass::runOn(ConstIntExpr& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stmt.setType(stmt.getTypeStmt()->getType());
}

void TypePass::runOn(VariableExpr& stmt) {
    stmt.setType(stmt.getVariableDefStmt()->getTypeStmt()->getType());
}
