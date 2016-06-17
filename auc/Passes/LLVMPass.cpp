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
    : ASTPass(ast), llvmContext(ast.getLLVMContext()),
    irBuilder(ast.getIRBuilder()), currentBlock(nullptr) {
}

void LLVMPass::createLLVMTypes() {
    for (std::pair<std::string, ASTPtr<Type>> type : ast.getTypes()) {
        type.second->createLLVMType(llvmContext);
    }
}

void LLVMPass::run() {
    createLLVMTypes();
    currentBlock = nullptr;
    for (ASTPtr<Declaration> decl : ast.getDeclarations()) {
        decl->runPass(*this);
    }
}

void LLVMPass::runOn(FunctionDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    /// Create function type and function
    for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
        func.getParameterLLVMTypes().push_back(
            innerStmt->getTypeStmt()->getType()->getLLVMType());
    }
    llvm::Function* llvmFunction = llvm::Function::Create(
        llvm::FunctionType::get(
        func.getReturnTypeStmt()->getType()->getLLVMType(),
        func.getParameterLLVMTypes(), false),
        llvm::Function::ExternalLinkage, func.getName(), &ast.getLLVMModule());
    func.setLLVMFunction(llvmFunction);
    currentBlock = &func.getBody();
    llvm::BasicBlock* llvmBlock = llvm::BasicBlock::Create(llvmContext, "entry",
        llvmFunction);
    currentBlock->setLLVMBlock(llvmBlock);
    irBuilder.SetInsertPoint(llvmBlock);
    /// Add alloca for each parameter
    ASTList<VariableDefStmt>::iterator paramIter = func.getParameters().begin();
    for (llvm::Value& parameter : llvmFunction->args()) {
        parameter.setName((*paramIter)->getName());
        (*paramIter)->runPass(*this);

        /// Store the initial value into the alloca
        irBuilder.CreateStore(&parameter,
            (*paramIter)->getAllocaInst());

        /// \todo Add arguments to variable symbol table?
    }
    func.getBody().runPass(*this);
}

void LLVMPass::runOn(MethodDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    func.getObjectTypeStmt()->runPass(*this);
    /// Create function type and function
    for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
        func.getParameterLLVMTypes().push_back(
            innerStmt->getTypeStmt()->getType()->getLLVMType());
    }
    llvm::Function* llvmFunction = llvm::Function::Create(
        llvm::FunctionType::get(
        func.getReturnTypeStmt()->getType()->getLLVMType(),
        func.getParameterLLVMTypes(), false),
        llvm::Function::ExternalLinkage, func.getName(), &ast.getLLVMModule());
    func.setLLVMFunction(llvmFunction);
    currentBlock = &func.getBody();
    llvm::BasicBlock* llvmBlock = llvm::BasicBlock::Create(llvmContext, "entry",
        llvmFunction);
    currentBlock->setLLVMBlock(llvmBlock);
    irBuilder.SetInsertPoint(llvmBlock);
    /// Add alloca for each parameter
    ASTList<VariableDefStmt>::iterator paramIter = func.getParameters().begin();
    for (llvm::Value& parameter : llvmFunction->args()) {
        parameter.setName((*paramIter)->getName());
        (*paramIter)->runPass(*this);

        /// Store the initial value into the alloca
        irBuilder.CreateStore(&parameter,
            (*paramIter)->getAllocaInst());

        /// \todo Add arguments to variable symbol table?
    }
    func.getBody().runPass(*this);
}

void LLVMPass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
    irBuilder.CreateRet(stmt.getValue()->getLLVMValue());
}

void LLVMPass::runOn(VariableDefStmt& stmt) {
    /// Create an alloca for this variable
    stmt.getTypeStmt()->runPass(*this);
    stmt.setAllocaInst(irBuilder.CreateAlloca(
        stmt.getTypeStmt()->getType()->getLLVMType(),
        0, stmt.getName()));
}

void LLVMPass::runOn(VariableDefAssignStmt& stmt) {
    stmt.getTypeStmt()->runPass(*this);
    llvm::AllocaInst* allocaInst = irBuilder.CreateAlloca(
        stmt.getTypeStmt()->getType()->getLLVMType(),
        0, stmt.getName());
    stmt.setAllocaInst(allocaInst);
    stmt.getValue()->runPass(*this);
    irBuilder.CreateStore(allocaInst,
        stmt.getValue()->getLLVMValue());
    /// \todo Merge getLLVMValue and getAllocaInst in Expression subclasses?
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
    std::vector<llvm::Value*> parameters;
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        expr->runPass(*this);
        parameters.push_back(expr->getLLVMValue());
    }
    stmt.setLLVMValue(irBuilder.CreateCall(
        stmt.getFunctionDef()->getLLVMFunction(), parameters));
}

void LLVMPass::runOn(MethodCallExpr& stmt) {
    stmt.getObjectExpr()->runPass(*this);
    std::vector<llvm::Value*> parameters;
    for (ASTPtr<Expression> expr : stmt.getParameters()) {
        expr->runPass(*this);
        parameters.push_back(expr->getLLVMValue());
    }
    stmt.setLLVMValue(irBuilder.CreateCall(
        stmt.getMethodDef()->getLLVMFunction(), parameters));
}

void LLVMPass::runOn(ConstUInt32Expr& stmt) {
    stmt.setLLVMValue(llvm::ConstantInt::get(llvmContext,
        llvm::APInt(32u, (uint64_t) stmt.getNumValue(), false)));
}

void LLVMPass::runOn(VariableExpr& stmt) {
    stmt.setLLVMValue(stmt.getVariableDefStmt()->getAllocaInst());
}
