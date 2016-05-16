/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ValueExpressions.hpp"

#include <sstream>

using namespace AST;

VariableExpr::VariableExpr(std::string name) : name(name) {

}

void FunctionCallExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void FunctionCallExpr::runPassOnChildren(ASTPass& pass) {
    for (ASTPtr<ValueExpr> expression : parameters) {
        expression->runPass(pass);
    }
}

void ConstIntExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
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

void UnaryOpExpr::runPassOnChildren(ASTPass& pass) {
    operand->runPass(pass);
}

std::string UnaryOpExpr::getName() {
    return name;
}


BinaryOpExpr::BinaryOpExpr(std::string name, ASTPtr<ValueExpr> operand1,
    ASTPtr<ValueExpr> operand2)
    : name(name), operand1(operand1), operand2(operand2) {
}

void BinaryOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void BinaryOpExpr::runPassOnChildren(ASTPass& pass) {
    operand1->runPass(pass);
    operand2->runPass(pass);
}

std::string BinaryOpExpr::getName() {
    return name;
}


UnaryAssignOpExpr::UnaryAssignOpExpr(std::string name,
    ASTPtr<VariableExpr> variable)
    : name(name), variable(variable) {
}

void UnaryAssignOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void UnaryAssignOpExpr::runPassOnChildren(ASTPass& pass) {
    variable->runPass(pass);
}

std::string UnaryAssignOpExpr::getName() {
    return name;
}


BinaryAssignOpExpr::BinaryAssignOpExpr(std::string name,
    ASTPtr<VariableExpr> variable, ASTPtr<ValueExpr> operand)
    : name(name), variable(variable), operand(operand) {
}

void BinaryAssignOpExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void BinaryAssignOpExpr::runPassOnChildren(ASTPass& pass) {
    variable->runPass(pass);
    operand->runPass(pass);
}

std::string BinaryAssignOpExpr::getName() {
    return name;
}
