/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Expressions.hpp"
#include "Passes/ASTPass.hpp"
#include "Declarations.hpp"

using namespace AST;

Expression::Expression(CodeLocation codeLocation) : Statement(codeLocation) {
}


FunctionCallExpr::FunctionCallExpr(std::string name, CodeLocation codeLocation)
        : Expression(codeLocation), name(name), functionDecl(nullptr) {
}

void FunctionCallExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

TypePtr FunctionCallExpr::getType() {
    return functionDecl->getReturnTypeStmt()->getType();
}

std::string FunctionCallExpr::getName() {
    return name;
}

ASTList<Expression>& FunctionCallExpr::getArgs() {
    return args;
}

FunctionDecl* FunctionCallExpr::getFunctionDecl() {
    return functionDecl;
}

void FunctionCallExpr::setFunctionDecl(FunctionDecl* functionDecl) {
    this->functionDecl = functionDecl;
}


ConstIntExpr::ConstIntExpr(std::string valueStr, uint8_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("uint8", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int8_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("int8", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, uint16_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("uint16", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int16_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("int16", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, uint32_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("uint32", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int32_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("int32", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, uint64_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("uint64", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int64_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<TypeStmt>("int64", CodeLocation::none)) {
}

void ConstIntExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

TypePtr ConstIntExpr::getType() {
    return typeStmt->getType();
}

std::string ConstIntExpr::getValueStr() {
    return valueStr;
}

uint64_t ConstIntExpr::getNumValue() {
    return numValue;
}

TypeStmtPtr ConstIntExpr::getTypeStmt() {
    return typeStmt;
}


VariableExpr::VariableExpr(std::string name,
        CodeLocation codeLocation) : Expression(codeLocation),
        name(name), variableDefStmt(nullptr) {
}

void VariableExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

TypePtr VariableExpr::getType() {
    return variableDefStmt->getTypeStmt()->getType();
}

std::string VariableExpr::getName() {
    return name;
}

VariableDefStmt* VariableExpr::getVariableDefStmt() {
    return variableDefStmt;
}

void VariableExpr::setVariableDefStmt(VariableDefStmt* variableDefStmt) {
    this->variableDefStmt = variableDefStmt;
}
