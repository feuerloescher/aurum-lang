/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Expressions.hpp"
#include "ASTPass.hpp"
#include "Type.hpp"
#include "TypeStmt.hpp"

using namespace AST;

Expression::Expression(CodeLocation codeLocation)
    : Statement(codeLocation), llvmValue(nullptr) {
}

ASTPtr<Type> Expression::getType() {
    return type;
}

void Expression::setType(ASTPtr<Type> type) {
    this->type = type;
}

llvm::Value* Expression::getLLVMValue() {
    return llvmValue;
}

void Expression::setLLVMValue(llvm::Value* llvmValue) {
    this->llvmValue = llvmValue;
}


FunctionCallExpr::FunctionCallExpr(std::string name, CodeLocation codeLocation)
    : Expression(codeLocation), name(name), functionDef(nullptr) {
}

void FunctionCallExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionCallExpr::getName() {
    return name;
}

ASTList<Expression>& FunctionCallExpr::getArgs() {
    return args;
}

FunctionDef* FunctionCallExpr::getFunctionDef() {
    return functionDef;
}

void FunctionCallExpr::setFunctionDef(FunctionDef* functionDef) {
    this->functionDef = functionDef;
}


MethodCallExpr::MethodCallExpr(ASTPtr<Expression> objectExpr, std::string name,
    CodeLocation codeLocation)
    : Expression(codeLocation), objectExpr(objectExpr), name(name), methodDef(nullptr) {
}

void MethodCallExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

ASTPtr<Expression> MethodCallExpr::getObjectExpr() {
    return objectExpr;
}

std::string MethodCallExpr::getName() {
    return name;
}

std::string MethodCallExpr::getMangledName() {
    return objectExpr->getType()->getName() + '.' + name;
}

ASTList<Expression>& MethodCallExpr::getArgs() {
    return args;
}

MethodDef* MethodCallExpr::getMethodDef() {
    return methodDef;
}

void MethodCallExpr::setMethodDef(MethodDef* methodDef) {
    this->methodDef = methodDef;
}


ConstIntExpr::ConstIntExpr(std::string valueStr, uint8_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("uint8", CodeLocation::none)) {
}
ConstIntExpr::ConstIntExpr(std::string valueStr, int8_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("int8", CodeLocation::none)) {
}
ConstIntExpr::ConstIntExpr(std::string valueStr, uint16_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("uint16", CodeLocation::none)) {
}
ConstIntExpr::ConstIntExpr(std::string valueStr, int16_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("int16", CodeLocation::none)) {
}
ConstIntExpr::ConstIntExpr(std::string valueStr, uint32_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("uint32", CodeLocation::none)) {
}
ConstIntExpr::ConstIntExpr(std::string valueStr, int32_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("int32", CodeLocation::none)) {
}
ConstIntExpr::ConstIntExpr(std::string valueStr, uint64_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("uint64", CodeLocation::none)) {
}
ConstIntExpr::ConstIntExpr(std::string valueStr, int64_t numValue,
    CodeLocation codeLocation) : Expression(codeLocation),
    valueStr(valueStr), numValue((uint64_t) numValue),
    typeStmt(std::make_shared<TypeStmt>("int64", CodeLocation::none)) {
}

std::string ConstIntExpr::getValueStr() {
    return valueStr;
}

void ConstIntExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

uint64_t ConstIntExpr::getNumValue() {
    return numValue;
}

ASTPtr<TypeStmt> ConstIntExpr::getTypeStmt() {
    return typeStmt;
}


VariableExpr::VariableExpr(std::string name, CodeLocation codeLocation)
    : Expression(codeLocation), name(name), variableDefStmt(nullptr) {
}

void VariableExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
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
