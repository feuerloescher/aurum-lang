/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "LLVMPass.hpp"
#include "AST/AbstractSyntaxTree.hpp"
#include "AST/Declarations.hpp"
#include "AST/Statements.hpp"
#include "AST/Blocks.hpp"
#include "AST/TypeStmt.hpp"
#include "AST/Expressions.hpp"
#include "AST/Errors.hpp"
#include "AST/Type.hpp"

#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>

using namespace AST;
using namespace Passes;

LLVMPass::LLVMPass(AbstractSyntaxTree& ast)
    : ASTPass(ast), llvmContext(ast.getLLVMContext()), currentBlock(nullptr) {
}

void LLVMPass::run() {
    currentBlock = nullptr;
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void LLVMPass::runOn(FunctionDef& func) {
    func.getTypeStmt()->runPass(*this);
    currentBlock = &func.getBody();
    for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
        innerStmt->runPass(*this);
    }
    func.getBody().runPass(*this);
}

void LLVMPass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
}

void LLVMPass::runOn(VariableDefStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
}

void LLVMPass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    stmt.getValue()->runPass(*this);
}

void LLVMPass::runOn(Block& stmt) {
    currentBlock = &stmt;
    for (ASTPtr<Statement> innerStmt : stmt.getStatements()) {
        innerStmt->runPass(*this);
    }
    currentBlock = stmt.getParentBlock();
}

void LLVMPass::runOn(IfStmt& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void LLVMPass::runOn(WhileLoop& stmt) {
    stmt.getCondition()->runPass(*this);
    stmt.getBody().runPass(*this);
}

void LLVMPass::runOn(TypeStmt& stmt) {
}

void LLVMPass::runOn(FunctionCallExpr& stmt) {
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        expr->runPass(*this);
    }
}

void LLVMPass::runOn(ConstUInt32Expr& stmt) {
    stmt.setLLVMValue(llvm::ConstantInt::get(llvmContext,
        llvm::APInt(32u, (uint64_t) stmt.getNumValue(), false)));
}

void LLVMPass::runOn(VariableExpr& stmt) {
}

void LLVMPass::runOn(UnaryOpExpr& stmt) {
    stmt.getOperand()->runPass(*this);
}

void LLVMPass::runOn(BinaryOpExpr& stmt) {
    stmt.getOperand1()->runPass(*this);
    stmt.getOperand2()->runPass(*this);
}

void LLVMPass::runOn(UnaryAssignOpExpr& stmt) {
    stmt.getVariable()->runPass(*this);
}

void LLVMPass::runOn(BinaryAssignOpExpr& stmt) {
    stmt.getVariable()->runPass(*this);
    stmt.getOperand()->runPass(*this);
}
