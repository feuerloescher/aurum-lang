/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Statements.hpp"
#include "Passes/ASTPass.hpp"

using namespace AST;

Statement::Statement(CodeLocation codeLocation) : codeLocation(codeLocation) {
}

CodeLocation Statement::getCodeLocation() {
    return codeLocation;
}


ReturnStmt::ReturnStmt(ExpressionPtr value, CodeLocation codeLocation)
        : Statement(codeLocation), value(value) {
}

void ReturnStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ExpressionPtr ReturnStmt::getValue() {
    return value;
}


VariableDefStmt::VariableDefStmt(TypeStmtPtr typeStmt, std::string name, CodeLocation codeLocation)
        : Statement(codeLocation), typeStmt(typeStmt), name(name) {
}

void VariableDefStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string VariableDefStmt::getName() {
    return name;
}

TypeStmtPtr VariableDefStmt::getTypeStmt() {
    return typeStmt;
}


VariableDefAssignStmt::VariableDefAssignStmt(TypeStmtPtr type, std::string name, ExpressionPtr value,
        CodeLocation codeLocation) : VariableDefStmt(type, name, codeLocation), value(value) {
}

void VariableDefAssignStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ExpressionPtr VariableDefAssignStmt::getValue() {
    return value;
}
