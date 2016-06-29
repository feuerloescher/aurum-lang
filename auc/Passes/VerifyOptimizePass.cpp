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

using namespace AST;
using namespace Passes;

VerifyOptimizePass::VerifyOptimizePass(AbstractSyntaxTree& ast)
    : ASTPass(ast) {
    functionPassMgr = llvm::make_unique<llvm::legacy::FunctionPassManager>(
        &ast.getLLVMModule());
    modulePassMgr = llvm::make_unique<llvm::legacy::PassManager>();
    /// \todo Add other pass managers: loop, basic block, call graph ?

    for (llvm::legacy::PassManagerBase* passMgr
        : {(llvm::legacy::PassManagerBase*) functionPassMgr.get(),
        (llvm::legacy::PassManagerBase*) modulePassMgr.get()}) {

        passMgr->add(llvm::createVerifierPass());

        // Do simple "peephole" optimizations and bit-twiddling optzns.
        passMgr->add(llvm::createInstructionCombiningPass());
        // Reassociate expressions.
        passMgr->add(llvm::createReassociatePass());
        // Eliminate Common SubExpressions.
        passMgr->add(llvm::createGVNPass());
        // Simplify the control flow graph (deleting unreachable blocks, etc).
        passMgr->add(llvm::createCFGSimplificationPass());
    }
}

void VerifyOptimizePass::run() {
    functionPassMgr->doInitialization();
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
    functionPassMgr->doFinalization();

    modulePassMgr->run(ast.getLLVMModule());
}

void VerifyOptimizePass::runOn(FunctionDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    for (ASTPtr<VariableDefStmt> parameter : func.getParameters()) {
        parameter->runPass(*this);
    }
    func.getBody().runPass(*this);
    functionPassMgr->run(*func.getLLVMFunction());
}

void VerifyOptimizePass::runOn(MethodDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    func.getObjectTypeStmt()->runPass(*this);
    for (ASTPtr<VariableDefStmt> parameter : func.getParameters()) {
        parameter->runPass(*this);
    }
    func.getBody().runPass(*this);
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

void VerifyOptimizePass::runOn(ConstIntExpr& stmt) {
}

void VerifyOptimizePass::runOn(VariableExpr& stmt) {
}
