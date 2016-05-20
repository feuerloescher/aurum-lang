/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ValueExpressions.hpp"

#include <sstream>

using namespace AST;

FunctionCallExpr::FunctionCallExpr(std::string name) : name(name) {
}

void FunctionCallExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string FunctionCallExpr::getName() {
    return name;
}

ASTList<ValueExpr>& FunctionCallExpr::getParameters() {
    return parameters;
}


ConstIntExpr::ConstIntExpr(uint32_t value) : value(value) {
}

void ConstIntExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

uint32_t ConstIntExpr::getValue() {
    return value;
}


VariableExpr::VariableExpr(std::string name) : name(name) {

}

void VariableExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string VariableExpr::getName() {
    return name;
}


UnaryOpExpr::UnaryOpExpr(std::string name, ASTPtr<ValueExpr> operand)
    : name(name), operand(operand) {
}

void UnaryOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string UnaryOpExpr::getName() {
    return name;
}

ASTPtr<ValueExpr> UnaryOpExpr::getOperand() {
    return operand;
}


BinaryOpExpr::BinaryOpExpr(std::string name, ASTPtr<ValueExpr> operand1,
    ASTPtr<ValueExpr> operand2)
    : name(name), operand1(operand1), operand2(operand2) {
}

void BinaryOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

std::string BinaryOpExpr::getName() {
    return name;
}

ASTPtr<ValueExpr> BinaryOpExpr::getOperand1() {
    return operand1;
}

ASTPtr<ValueExpr> BinaryOpExpr::getOperand2() {
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
    ASTPtr<VariableExpr> variable, ASTPtr<ValueExpr> operand)
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

ASTPtr<ValueExpr> BinaryAssignOpExpr::getOperand() {
    return operand;
}
