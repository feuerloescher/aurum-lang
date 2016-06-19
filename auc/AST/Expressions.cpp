/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Expressions.hpp"
#include "ASTPass.hpp"
#include "Type.hpp"

using namespace AST;

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


FunctionCallExpr::FunctionCallExpr(std::string name) : name(name) {
}

void FunctionCallExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionCallExpr::getName() {
    return name;
}

ASTList<Expression>& FunctionCallExpr::getParameters() {
    return parameters;
}

FunctionDef* FunctionCallExpr::getFunctionDef() {
    return functionDef;
}

void FunctionCallExpr::setFunctionDef(FunctionDef* functionDef) {
    this->functionDef = functionDef;
}


MethodCallExpr::MethodCallExpr(ASTPtr<Expression> objectExpr, std::string name)
    : objectExpr(objectExpr), name(name), methodDef(nullptr) {
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

ASTList<Expression>& MethodCallExpr::getParameters() {
    return parameters;
}

MethodDef* MethodCallExpr::getMethodDef() {
    return methodDef;
}

void MethodCallExpr::setMethodDef(MethodDef* methodDef) {
    this->methodDef = methodDef;
}


ConstUInt32Expr::ConstUInt32Expr(uint32_t numValue) : numValue(numValue) {
}

void ConstUInt32Expr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

uint32_t ConstUInt32Expr::getNumValue() {
    return numValue;
}


VariableExpr::VariableExpr(std::string name)
    : name(name), variableDefStmt(nullptr) {
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
