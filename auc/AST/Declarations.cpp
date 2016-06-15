/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Declarations.hpp"

using namespace AST;

FunctionDef::FunctionDef(std::string name, ASTPtr<TypeStmt> type)
    : name(name), type(type) {
}

void FunctionDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionDef::getName() {
    return name;
}

ASTPtr<TypeStmt> FunctionDef::getTypeStmt() {
    return type;
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
