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

Declaration::Declaration(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
    CodeLocation codeLocation)
    : ASTElement(codeLocation), name(name), returnTypeStmt(returnTypeStmt),
    body(nullptr, codeLocation), llvmFunction(nullptr), exported(false) {
}

std::string Declaration::getName() {
    return name;
}

ASTPtr<TypeStmt> Declaration::getReturnTypeStmt() {
    return returnTypeStmt;
}

VariableDefStmtList& Declaration::getParameters() {
    return parameters;
}

Block& Declaration::getBody() {
    return body;
}

llvm::Function* Declaration::getLLVMFunction() {
    return llvmFunction;
}

void Declaration::setLLVMFunction(llvm::Function* llvmFunction) {
    this->llvmFunction = llvmFunction;
}

std::vector<llvm::Type*>& Declaration::getParameterLLVMTypes() {
    return parameterLLVMTypes;
}

bool Declaration::getExported() {
    return exported;
}

void Declaration::setExported(bool exported) {
    this->exported = exported;
}


FunctionDef::FunctionDef(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
    CodeLocation codeLocation)
    : Declaration(returnTypeStmt, name, codeLocation) {
}

void FunctionDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}


MethodDef::MethodDef(ASTPtr<TypeStmt> returnTypeStmt, std::string name,
        ASTPtr<TypeStmt> objectTypeStmt, CodeLocation codeLocation)
    : Declaration(returnTypeStmt, name, codeLocation),
    objectTypeStmt(objectTypeStmt) {
    this->name = returnTypeStmt->getName() + '.' + name;
    parameters.push_back(
        std::make_shared<VariableDefStmt>(objectTypeStmt, "this",
        &body, CodeLocation::none));
}

void MethodDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<TypeStmt> MethodDef::getObjectTypeStmt() {
    return objectTypeStmt;
}
