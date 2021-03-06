/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Expressions.hpp"
#include "Passes/ASTPass.hpp"
#include "Declarations.hpp"

using namespace AST;
using namespace type;

Expression::Expression(CodeLocation codeLocation) : Statement(codeLocation) {
}


FunctionCallExpr::FunctionCallExpr(std::string name, CodeLocation codeLocation)
        : Expression(codeLocation), name(name), functionDecl(nullptr) {
}

void FunctionCallExpr::runPass(ASTPass& pass) {
    pass.tryRunOn(*this);
}

TypePtr FunctionCallExpr::getType() {
    return functionDecl->getReturnTypeStmt()->getType();
}

bool FunctionCallExpr::getIsReference() {
    return functionDecl->getReturnTypeStmt()->getIsReference();
}

bool FunctionCallExpr::getIsReferenceable() {
    // you can't take the reference of a function return value
    return false;
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
        typeStmt(std::make_shared<BasicTypeStmt>("uint8", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int8_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<BasicTypeStmt>("int8", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, uint16_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<BasicTypeStmt>("uint16", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int16_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<BasicTypeStmt>("int16", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, uint32_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<BasicTypeStmt>("uint32", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int32_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<BasicTypeStmt>("int32", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, uint64_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<BasicTypeStmt>("uint64", CodeLocation::none)) {
}

ConstIntExpr::ConstIntExpr(std::string valueStr, int64_t numValue, CodeLocation codeLocation)
        : Expression(codeLocation), valueStr(valueStr), numValue((uint64_t) numValue),
        typeStmt(std::make_shared<BasicTypeStmt>("int64", CodeLocation::none)) {
}

void ConstIntExpr::runPass(ASTPass& pass) {
    pass.tryRunOn(*this);
}

TypePtr ConstIntExpr::getType() {
    return typeStmt->getType();
}

bool ConstIntExpr::getIsReference() {
    return false;
}

bool ConstIntExpr::getIsReferenceable() {
    return false;
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
    pass.tryRunOn(*this);
}

TypePtr VariableExpr::getType() {
    return variableDefStmt->getTypeStmt()->getType();
}

bool VariableExpr::getIsReference() {
    return variableDefStmt->getTypeStmt()->getIsReference();
}

bool VariableExpr::getIsReferenceable() {
    // if the variable is already a reference, you can't take a reference of it
    return !variableDefStmt->getTypeStmt()->getIsReference();
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
