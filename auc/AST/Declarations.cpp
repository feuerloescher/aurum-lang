/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Declarations.hpp"
#include "Passes/ASTPass.hpp"
#include "TypeStmt.hpp"
#include "Statements.hpp"

using namespace AST;

Declaration::Declaration(bool exported, CodeLocation codeLocation)
    : ASTElement(codeLocation), exported(exported)
{
}

bool Declaration::getExported() {
    return exported;
}

void Declaration::setExported(bool exported) {
    this->exported = exported;
}


FunctionDecl::FunctionDecl(TypeStmtPtr returnTypeStmt, std::string name, bool exported, CodeLocation codeLocation)
        : Declaration(exported, codeLocation), name(name), returnTypeStmt(returnTypeStmt) {
}

void FunctionDecl::runPass(ASTPass& pass) {
    pass.tryRunOn(*this);
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


FunctionDef::FunctionDef(FunctionDeclPtr funcDecl, BlockPtr body, CodeLocation codeLocation)
        : Declaration(funcDecl->getExported(), codeLocation), funcDecl(funcDecl), body(body) {
}

void FunctionDef::runPass(ASTPass& pass) {
    pass.tryRunOn(*this);
}

std::string FunctionDef::getName() {
    return funcDecl->getName();
}

FunctionDeclPtr FunctionDef::getFunctionDecl() {
    return funcDecl;
}

BlockPtr FunctionDef::getBody() {
    return body;
}
