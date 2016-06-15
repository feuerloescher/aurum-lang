/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Expressions.hpp"

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


UnaryOpExpr::UnaryOpExpr(std::string name, ASTPtr<Expression> operand)
    : name(name), operand(operand) {
}

void UnaryOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string UnaryOpExpr::getName() {
    return name;
}

ASTPtr<Expression> UnaryOpExpr::getOperand() {
    return operand;
}


BinaryOpExpr::BinaryOpExpr(std::string name, ASTPtr<Expression> operand1,
    ASTPtr<Expression> operand2)
    : name(name), operand1(operand1), operand2(operand2) {
}

void BinaryOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string BinaryOpExpr::getName() {
    return name;
}

ASTPtr<Expression> BinaryOpExpr::getOperand1() {
    return operand1;
}

ASTPtr<Expression> BinaryOpExpr::getOperand2() {
    return operand2;
}


UnaryAssignOpExpr::UnaryAssignOpExpr(std::string name,
    ASTPtr<VariableExpr> variable)
    : name(name), variable(variable) {
}

void UnaryAssignOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string UnaryAssignOpExpr::getName() {
    return name;
}

ASTPtr<VariableExpr> UnaryAssignOpExpr::getVariable() {
    return variable;
}


BinaryAssignOpExpr::BinaryAssignOpExpr(std::string name,
    ASTPtr<VariableExpr> variable, ASTPtr<Expression> operand)
    : name(name), variable(variable), operand(operand) {
}

void BinaryAssignOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string BinaryAssignOpExpr::getName() {
    return name;
}

ASTPtr<VariableExpr> BinaryAssignOpExpr::getVariable() {
    return variable;
}

ASTPtr<Expression> BinaryAssignOpExpr::getOperand() {
    return operand;
}
