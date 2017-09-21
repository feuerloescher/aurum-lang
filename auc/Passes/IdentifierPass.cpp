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
using namespace type;

IdentifierPass::IdentifierPass(AbstractSyntaxTree& ast)
    : ASTPass(ast), currentBlock(nullptr), onlyInsertDeclarations(true) {
}

void IdentifierPass::run() {
    currentBlock = nullptr;
    onlyInsertDeclarations = true;
    for (FunctionDeclPtr func : ast.getStdLibFunctionDecls()) {
        func->runPass(*this);
    }
    for (DeclarationPtr decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
    currentBlock = nullptr;
    onlyInsertDeclarations = false;
    for (DeclarationPtr decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void IdentifierPass::runOn(AST::FunctionDecl& funcDecl) {
    funcDecl.getReturnTypeStmt()->runPass(*this);
    for (VariableDefStmtPtr innerStmt : funcDecl.getParameters()) {
        innerStmt->runPass(*this);
    }
    // TODO: move the type getting code to FunctionDecl class
    TypePtr type;
    if (funcDecl.getParameters().size() > 0) {
        type = funcDecl.getParameters().front()->getTypeStmt()->getType();
    } else {
        type = ast.getTypes().find("void");
    }
    type->getFunctionDecls().insert(&funcDecl, funcDecl.getCodeLocation());
}

void IdentifierPass::runOn(FunctionDef& func) {
    if (onlyInsertDeclarations) {
        Block* lastCurrentBlock = currentBlock;
        currentBlock = func.getBody().get();
        func.getFunctionDecl()->runPass(*this);
        currentBlock = lastCurrentBlock;
        ast.getFunctionDefs().insert(&func, func.getCodeLocation());
    } else {
        func.getBody()->runPass(*this);
    }
}

void IdentifierPass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void IdentifierPass::runOn(VariableDefStmt& stmt) {
    // if currentBlock==nullptr, 'stmt' is a parameter definition of a
    // FunctionDeclStmt, so there is no block to insert the variables into
    if (currentBlock) {
        currentBlock->getVariables().insert(&stmt, stmt.getCodeLocation());
    }
    stmt.getTypeStmt()->runPass(*this);
}

void IdentifierPass::runOn(VariableDefAssignStmt& stmt) {
    currentBlock->getVariables().insert(&stmt, stmt.getCodeLocation());
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

void IdentifierPass::runOn(BasicTypeStmt& stmt) {
    TypePtr type = ast.getTypes().find(stmt.getName());
    if (!type) {
        throw UnknownIdentifierError(stmt.getCodeLocation(), stmt.getName());
    }
    stmt.setType(type);
}

void IdentifierPass::runOn(FunctionCallExpr& stmt) {
    for (ExpressionPtr expr : stmt.getArgs()) {
        expr->runPass(*this);
    }
    // TODO: move the type getting code to FunctionCallExpr class
    TypePtr type;
    if (stmt.getArgs().size() > 0) {
        type = stmt.getArgs().front()->getType();
    } else {
        type = ast.getTypes().find("void");
    }
    FunctionDecl* functionDecl = type->getFunctionDecls().find(stmt.getName());
    if (!functionDecl) {
        throw UnknownIdentifierError(stmt.getCodeLocation(), stmt.getName());
    }
    if (stmt.getArgs().size() != functionDecl->getParameters().size()) {
        throw ArgumentCountError(stmt.getCodeLocation(), stmt.getName(),
            functionDecl->getParameters().size(), stmt.getArgs().size());
    }
    stmt.setFunctionDecl(functionDecl);
}

void IdentifierPass::runOn(ConstIntExpr& stmt) {
    stmt.getTypeStmt()->runPass(*this);
}

void IdentifierPass::runOn(VariableExpr& stmt) {
    /// \todo Copy variables from parent blocks in runOn(Block),
    /// or search through parent blocks here
    VariableDefStmt* variableDef = currentBlock->getVariables().find(stmt.getName());
    if (!variableDef) {
        throw UnknownIdentifierError(stmt.getCodeLocation(), stmt.getName());
    }
    stmt.setVariableDefStmt(variableDef);
}
