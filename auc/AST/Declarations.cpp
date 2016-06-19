/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Declarations.hpp"
#include "ASTPass.hpp"
#include "TypeStmt.hpp"
#include "Type.hpp"

using namespace AST;

FunctionDef::FunctionDef(std::string name, ASTPtr<TypeStmt> returnTypeStmt)
    : name(name), returnTypeStmt(returnTypeStmt), llvmFunction(nullptr) {
}

void FunctionDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionDef::getName() {
    return name;
}

ASTPtr<TypeStmt> FunctionDef::getReturnTypeStmt() {
    return returnTypeStmt;
}

VariableDefStmtList& FunctionDef::getParameters() {
    return parameters;
}

Block& FunctionDef::getBody() {
    return body;
}

llvm::Function* FunctionDef::getLLVMFunction() {
    return llvmFunction;
}

void FunctionDef::setLLVMFunction(llvm::Function* llvmFunction) {
    this->llvmFunction = llvmFunction;
}

std::vector<llvm::Type*>& FunctionDef::getParameterLLVMTypes() {
    return parameterLLVMTypes;
}


MethodDef::MethodDef(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
        ASTPtr<TypeStmt> objectTypeStmt)
    : returnTypeStmt(returnTypeStmt),
    objectTypeStmt(objectTypeStmt), llvmFunction(nullptr) {
    this->name = returnTypeStmt->getName() + '.' + name;
    parameters.push_back(
        std::make_shared<VariableDefStmt>("this", objectTypeStmt));
}

void MethodDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string MethodDef::getName() {
    return name;
}

ASTPtr<TypeStmt> MethodDef::getReturnTypeStmt() {
    return returnTypeStmt;
}

ASTPtr<TypeStmt> MethodDef::getObjectTypeStmt() {
    return objectTypeStmt;
}

VariableDefStmtList& MethodDef::getParameters() {
    return parameters;
}

Block& MethodDef::getBody() {
    return body;
}

llvm::Function* MethodDef::getLLVMFunction() {
    return llvmFunction;
}

void MethodDef::setLLVMFunction(llvm::Function* llvmFunction) {
    this->llvmFunction = llvmFunction;
}

std::vector<llvm::Type*>& MethodDef::getParameterLLVMTypes() {
    return parameterLLVMTypes;
}
