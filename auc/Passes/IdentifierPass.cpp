/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include <cassert>
#include "IdentifierPass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Expressions.hpp"
#include "AST/Errors.hpp"
#include "Types/Type.hpp"

using namespace AST;
using namespace Passes;

IdentifierPass::IdentifierPass(AbstractSyntaxTree& ast)
    : ASTPass(ast), currentBlock(nullptr), onlyInsertDeclarations(true) {
}

void IdentifierPass::run() {
    ast.getFunctionDefs().clear();
    currentBlock = nullptr;
    onlyInsertDeclarations = true;
    for (ASTElementPtr elem : ast.getASTElements()) {
        elem->runPass(*this);
    }
    currentBlock = nullptr;
    onlyInsertDeclarations = false;
    for (ASTElementPtr elem : ast.getASTElements()) {
        elem->runPass(*this);
    }
}

void IdentifierPass::runOn(FunctionDef& func) {
    if (onlyInsertDeclarations) {
        if (!ast.getFunctionDefs().insert(&func)) {
            throw ExistingIdentifierError(func.getName());
        }
        func.getFunctionDecl()->getReturnTypeStmt()->runPass(*this);
        Block* lastCurrentBlock = currentBlock;
        currentBlock = func.getBody().get();
        for (VariableDefStmtPtr innerStmt : func.getFunctionDecl()->getParameters()) {
            innerStmt->runPass(*this);
        }
        currentBlock = lastCurrentBlock;
    } else {
        func.getBody()->runPass(*this);
    }
}

void IdentifierPass::runOn(MethodDef& func) {
    if (onlyInsertDeclarations) {
        func.getReturnTypeStmt()->runPass(*this);
        func.getObjectTypeStmt()->runPass(*this);
        if (!func.getObjectTypeStmt()->getType()->getMethodDefs()
                .insert(&func)) {
            throw ExistingIdentifierError(func.getName());
        }
        Block* lastCurrentBlock = currentBlock;
        currentBlock = func.getBody().get();
        for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
            innerStmt->runPass(*this);
        }
        currentBlock = lastCurrentBlock;
    } else {
        func.getBody()->runPass(*this);
    }
}

void IdentifierPass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void IdentifierPass::runOn(VariableDefStmt& stmt) {
    if (!currentBlock->getVariables().insert(&stmt)) {
        throw ExistingIdentifierError(stmt.getName());
    }
    stmt.getTypeStmt()->runPass(*this);
}

void IdentifierPass::runOn(VariableDefAssignStmt& stmt) {
    if (!currentBlock->getVariables().insert(&stmt)) {
        throw ExistingIdentifierError(stmt.getName());
    }
    stmt.getTypeStmt()->runPass(*this);
    stmt.getValue()->runPass(*this);
}

void IdentifierPass::runOn(Block& stmt) {
    Block* lastCurrentBlock = currentBlock;
    currentBlock = &stmt;
    for (StatementPtr innerStmt : stmt.getStatements()) {
        innerStmt->runPass(*this);
    }
    currentBlock = lastCurrentBlock;
}

void IdentifierPass::runOn(IfStmt& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody()->runPass(*this);
}

void IdentifierPass::runOn(WhileLoop& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void IdentifierPass::runOn(TypeStmt& stmt) {
    TypePtr type = ast.getTypes().find(stmt.getName());
    if (!type) {
        throw UnknownIdentifierError(stmt.getName());
    }
    stmt.setType(type);
}

void IdentifierPass::runOn(FunctionCallExpr& stmt) {
    for (ExpressionPtr expr : stmt.getArgs()) {
        expr->runPass(*this);
    }
    FunctionDef* functionDef = ast.getFunctionDefs().find(stmt.getName());
    if (!functionDef) {
        throw UnknownIdentifierError(stmt.getName());
    }
    if (stmt.getArgs().size() != functionDef->getFunctionDecl()->getParameters().size()) {
        throw ArgumentCountError(stmt.getName(),
            functionDef->getFunctionDecl()->getParameters().size(), stmt.getArgs().size());
    }
    stmt.setFunctionDef(functionDef);
}

void IdentifierPass::runOn(MethodCallExpr& stmt) {
    stmt.getObjectExpr()->runPass(*this);
    for (ExpressionPtr expr : stmt.getArgs()) {
        expr->runPass(*this);
    }
    /// Method identifier is resolved in TypePass, as type of
    /// stmt.getObjectExpr() is not resolved yet
}

void IdentifierPass::runOn(ConstIntExpr& stmt) {
    stmt.getTypeStmt()->runPass(*this);
}

void IdentifierPass::runOn(VariableExpr& stmt) {
    /// \todo Copy variables from parent blocks in runOn(Block),
    /// or search through parent blocks here
    VariableDefStmt* variableDef = currentBlock->getVariables().find(stmt.getName());
    if (!variableDef) {
        throw UnknownIdentifierError(stmt.getName());
    }
    stmt.setVariableDefStmt(variableDef);
}
