/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Declarations.hpp"
#include "ASTPass.hpp"
#include "TypeStmt.hpp"
#include "Statements.hpp"

using namespace AST;

FunctionDecl::FunctionDecl(TypeStmtPtr returnTypeStmt, std::string name, CodeLocation codeLocation)
        : ASTElement(codeLocation), name(name), returnTypeStmt(returnTypeStmt), exported(false) {
}

std::string FunctionDecl::getName() {
    return name;
}

TypeStmtPtr FunctionDecl::getReturnTypeStmt() {
    return returnTypeStmt;
}

VariableDefStmtList& FunctionDecl::getParameters() {
    return parameters;
}

bool FunctionDecl::getExported() {
    return exported;
}

void FunctionDecl::setExported(bool exported) {
    this->exported = exported;
}


FunctionDef::FunctionDef(FunctionDeclPtr funcDecl, BlockPtr body, CodeLocation codeLocation)
        : ASTElement(codeLocation), funcDecl(funcDecl), body(body) {
}

void FunctionDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

FunctionDeclPtr FunctionDef::getFunctionDecl() {
    return funcDecl;
}

BlockPtr FunctionDef::getBody() {
    return body;
}


MethodDef::MethodDef(TypeStmtPtr returnTypeStmt, std::string name,
        TypeStmtPtr objectTypeStmt, CodeLocation codeLocation)
        : ASTElement(codeLocation),
        objectTypeStmt(objectTypeStmt) {
    this->name = objectTypeStmt->getName() + '.' + name;
    parameters.push_back(
            std::make_shared<VariableDefStmt>(objectTypeStmt, "this", CodeLocation::none));
}

void MethodDef::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

TypeStmtPtr MethodDef::getReturnTypeStmt() {
    return returnTypeStmt;
}

TypeStmtPtr MethodDef::getObjectTypeStmt() {
    return objectTypeStmt;
}

VariableDefStmtList& MethodDef::getParameters() {
    return parameters;
}

BlockPtr MethodDef::getBody() {
    return body;
}
