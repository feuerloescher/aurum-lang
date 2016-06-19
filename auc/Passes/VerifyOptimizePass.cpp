/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "VerifyOptimizePass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Expressions.hpp"
#include "AST/Errors.hpp"
#include "AST/Type.hpp"

#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/Scalar.h>

#include <clang/Basic/Version.h>
#if CLANG_VERSION_MINOR >= 9
    #include <llvm/Transforms/Scalar/GVN.h>
#endif

using namespace AST;
using namespace Passes;

VerifyOptimizePass::VerifyOptimizePass(AbstractSyntaxTree& ast)
    : ASTPass(ast) {
    functionPassMgr = llvm::make_unique<llvm::legacy::FunctionPassManager>(
        &ast.getLLVMModule());

    // Do simple "peephole" optimizations and bit-twiddling optzns.
    functionPassMgr->add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    functionPassMgr->add(llvm::createReassociatePass());
    // Eliminate Common SubExpressions.
    functionPassMgr->add(llvm::createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    functionPassMgr->add(llvm::createCFGSimplificationPass());

    functionPassMgr->doInitialization();
}

void VerifyOptimizePass::run() {
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void VerifyOptimizePass::runOn(FunctionDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    for (ASTPtr<VariableDefStmt> parameter : func.getParameters()) {
        parameter->runPass(*this);
    }
    func.getBody().runPass(*this);
    llvm::verifyFunction(*func.getLLVMFunction());
    functionPassMgr->run(*func.getLLVMFunction());
}

void VerifyOptimizePass::runOn(MethodDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    func.getObjectTypeStmt()->runPass(*this);
    for (ASTPtr<VariableDefStmt> parameter : func.getParameters()) {
        parameter->runPass(*this);
    }
    func.getBody().runPass(*this);
    llvm::verifyFunction(*func.getLLVMFunction());
    functionPassMgr->run(*func.getLLVMFunction());
}

void VerifyOptimizePass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void VerifyOptimizePass::runOn(VariableDefStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
}

void VerifyOptimizePass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stmt.getValue()->runPass(*this);
}

void VerifyOptimizePass::runOn(Block& stmt) {
    for (ASTPtr<Statement> innerStmt : stmt.getStatements()) {
        innerStmt->runPass(*this);
    }
}

void VerifyOptimizePass::runOn(IfStmt& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void VerifyOptimizePass::runOn(WhileLoop& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void VerifyOptimizePass::runOn(TypeStmt& stmt) {
}

void VerifyOptimizePass::runOn(FunctionCallExpr& stmt) {
    for (ASTPtr<Expression> expr : stmt.getArgs()) {
        expr->runPass(*this);
    }
}

void VerifyOptimizePass::runOn(MethodCallExpr& stmt) {
    stmt.getObjectExpr()->runPass(*this);
    for (ASTPtr<Expression> expr : stmt.getArgs()) {
        expr->runPass(*this);
    }
}

void VerifyOptimizePass::runOn(ConstUInt32Expr& stmt) {
}

void VerifyOptimizePass::runOn(VariableExpr& stmt) {
}
