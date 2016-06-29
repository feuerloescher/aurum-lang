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
#include "AST/ScalarTypes.hpp"

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

void LLVMPass::addScalarMethods() {
    for (bool isSigned : {false, true}) {
        for (unsigned int width : {8, 16, 32, 64}) {
            std::string intTypeName =
                (isSigned ? "int" : "uint") + std::to_string(width);
            for (std::string op : {"+", "-", "*", "/", "="}) {
                std::string methodName = intTypeName + '.' + op;
                std::shared_ptr<MethodDef> intMethod =
                    ast.getStdLibMethodDefs().find(methodName);
                if (!intMethod) {
                    throw UnknownIdentifierError(methodName);
                }
                intMethod->runPass(*this);
                llvm::Value* thisPtr =
                    intMethod->getParameters()[0]->getAllocaInst();
                llvm::Value* paramPtr =
                    intMethod->getParameters()[1]->getAllocaInst();
                llvm::Value* thisValue = irBuilder.CreateLoad(
                    thisPtr, "thisval");
                llvm::Value* paramValue = irBuilder.CreateLoad(
                    paramPtr, "paramval");
                llvm::Value* retValue = nullptr;
                if (op == "+") {
                    retValue =
                        irBuilder.CreateAdd(thisValue, paramValue, "addtmp");
                } else if (op == "-") {
                    retValue =
                        irBuilder.CreateSub(thisValue, paramValue, "subtmp");
                } else if (op == "*") {
                    retValue =
                        irBuilder.CreateMul(thisValue, paramValue, "multmp");
                } else if (op == "/") {
                    if (isSigned) {
                        retValue = irBuilder.CreateSDiv(
                            thisValue, paramValue, "divtmp");
                    } else {
                        retValue = irBuilder.CreateUDiv(
                            thisValue, paramValue, "divtmp");
                    }
                } else if (op == "=") {
                    irBuilder.CreateStore(paramValue, thisPtr);
                    retValue = paramValue;
                }
                irBuilder.CreateRet(retValue);
            }
            llvm::Value* constantOne = llvm::ConstantInt::get(llvmContext,
                llvm::APInt(width, (uint64_t) 1, isSigned));
            for (std::string op : {"++", "--"}) {
                std::string methodName = intTypeName + '.' + op;
                std::shared_ptr<MethodDef> intMethod =
                    ast.getStdLibMethodDefs().find(methodName);
                if (!intMethod) {
                    throw UnknownIdentifierError(methodName);
                }
                intMethod->runPass(*this);
                llvm::Value* thisPtr =
                    intMethod->getParameters()[0]->getAllocaInst();
                llvm::Value* thisValue = irBuilder.CreateLoad(
                    thisPtr, "thisval");
                llvm::Value* retValue = nullptr;
                if (op == "++") {
                    retValue =
                        irBuilder.CreateAdd(thisValue, constantOne, "inctmp");
                } else if (op == "--") {
                    retValue =
                        irBuilder.CreateSub(thisValue, constantOne, "dectmp");
                }
                irBuilder.CreateStore(retValue, thisPtr);
                irBuilder.CreateRet(retValue);
            }
        }
    }
}

void LLVMPass::run() {
    createLLVMTypes();
    addScalarMethods();
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
        assert(paramIter != func.getParameters().end());
        parameter.setName((*paramIter)->getName());
        (*paramIter)->runPass(*this);

        /// Store the initial value into the alloca
        irBuilder.CreateStore(&parameter,
            (*paramIter)->getAllocaInst());

        ++paramIter;
    }
    assert(paramIter == func.getParameters().end());
    func.getBody().runPass(*this);
}

void LLVMPass::runOn(MethodDef& func) {
    func.getReturnTypeStmt()->runPass(*this);
    func.getObjectTypeStmt()->runPass(*this);
    /// Create function type and function
    int i = 0;
    for (ASTPtr<VariableDefStmt> innerStmt : func.getParameters()) {
        llvm::Type* llvmType =
            innerStmt->getTypeStmt()->getType()->getLLVMType();
        if (i++ == 0) {
            llvmType = llvmType->getPointerTo();
        }
        func.getParameterLLVMTypes().push_back(llvmType);
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
    /// \todo Set pointer of first parameter 'this'
    ASTList<VariableDefStmt>::iterator paramIter = func.getParameters().begin();
    for (llvm::Value& llvmParam : llvmFunction->args()) {
        assert(paramIter != func.getParameters().end());
        ASTPtr<VariableDefStmt> param = *paramIter;
        llvmParam.setName(param->getName());
        if (param->getName() == "this") {
            /// Create no alloca for "this" pointer
            param->getTypeStmt()->runPass(*this);
            param->setAllocaInst((llvm::AllocaInst*) &llvmParam);
        } else {
            param->runPass(*this);

            /// Store the initial value into the alloca
            irBuilder.CreateStore(&llvmParam, param->getAllocaInst());
        }

        ++paramIter;
    }
    assert(paramIter == func.getParameters().end());
    func.getBody().runPass(*this);
}

void LLVMPass::runOn(ReturnStmt& stmt) {
    stmt.getValue()->runPass(*this);
    ASTPtr<Expression> expr = stmt.getValue();
    /// Return by-value
    if (expr->getLLVMValue()->getType()->isPointerTy()) {
        irBuilder.CreateRet(irBuilder.CreateLoad(expr->getLLVMValue(),
            expr->getLLVMValue()->getName() + ".val"));
    } else {
        irBuilder.CreateRet(expr->getLLVMValue());
    }
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
    irBuilder.CreateStore(stmt.getValue()->getLLVMValue(), allocaInst);
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
    for (ASTPtr<Expression> expr : stmt.getArgs()) {
        expr->runPass(*this);
        /// Parameters are call-by-value
        if (expr->getLLVMValue()->getType()->isPointerTy()) {
            parameters.push_back(irBuilder.CreateLoad(expr->getLLVMValue(),
                expr->getLLVMValue()->getName() + ".val"));
        } else {
            parameters.push_back(expr->getLLVMValue());
        }
    }
    stmt.setLLVMValue(irBuilder.CreateCall(
        stmt.getFunctionDef()->getLLVMFunction(), parameters));
}

void LLVMPass::runOn(MethodCallExpr& stmt) {
    stmt.getObjectExpr()->runPass(*this);
    std::vector<llvm::Value*> parameters;

    /// First parameter is call-by-reference
    if (stmt.getObjectExpr()->getLLVMValue()->getType()->isPointerTy()) {
        parameters.push_back(stmt.getObjectExpr()->getLLVMValue());
    } else {
        llvm::AllocaInst* allocaInst = irBuilder.CreateAlloca(
            stmt.getObjectExpr()->getType()->getLLVMType(),
            0, "thistmp");
        irBuilder.CreateStore(stmt.getObjectExpr()->getLLVMValue(), allocaInst);
        parameters.push_back(allocaInst);
    }

    for (ASTPtr<Expression> expr : stmt.getArgs()) {
        expr->runPass(*this);
        /// Other parameters are call-by-value
        if (expr->getLLVMValue()->getType()->isPointerTy()) {
            parameters.push_back(irBuilder.CreateLoad(expr->getLLVMValue(),
                expr->getLLVMValue()->getName() + ".val"));
        } else {
            parameters.push_back(expr->getLLVMValue());
        }
    }
    stmt.setLLVMValue(irBuilder.CreateCall(
        stmt.getMethodDef()->getLLVMFunction(), parameters));
}

void LLVMPass::runOn(ConstIntExpr& stmt) {
    stmt.setLLVMValue(llvm::ConstantInt::get(
        stmt.getTypeStmt()->getType()->getLLVMType(),
        stmt.getNumValue(),
        std::static_pointer_cast<IntType>(
            stmt.getTypeStmt()->getType())->getSigned()));
}

void LLVMPass::runOn(VariableExpr& stmt) {
    stmt.setLLVMValue(stmt.getVariableDefStmt()->getAllocaInst());
}
