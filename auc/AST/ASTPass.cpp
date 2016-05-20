/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTPass.hpp"

#include <stdexcept>

using namespace AST;

ASTPass::ASTPass(AbstractSyntaxTree& ast) : ast(ast) {
}

void ASTPass::runOn(Declaration& expr) {
    throw std::runtime_error("Declaration unhandled");
}
void ASTPass::runOn(FunctionDef& expr) {
    throw std::runtime_error("FunctionDef unhandled");
}

void ASTPass::runOn(Statement& expr) {
    throw std::runtime_error("Statement unhandled");
}
void ASTPass::runOn(ReturnStmt& expr) {
    throw std::runtime_error("ReturnStmt unhandled");
}
void ASTPass::runOn(VariableDefStmt& expr) {
    throw std::runtime_error("VariableDefStmt unhandled");
}
void ASTPass::runOn(VariableDefAssignStmt& expr) {
    throw std::runtime_error("VariableDefAssignStmt unhandled");
}

void ASTPass::runOn(Block& expr) {
    throw std::runtime_error("Block unhandled");
}
void ASTPass::runOn(IfStmt& expr) {
    throw std::runtime_error("IfStmt unhandled");
}
void ASTPass::runOn(WhileLoop& expr) {
    throw std::runtime_error("WhileLoop unhandled");
}

void ASTPass::runOn(Type& expr) {
    throw std::runtime_error("Type unhandled");
}

void ASTPass::runOn(Expression& expr) {
    throw std::runtime_error("Expression unhandled");
}
void ASTPass::runOn(FunctionCallExpr& expr) {
    throw std::runtime_error("FunctionCallExpr unhandled");
}
void ASTPass::runOn(ConstIntExpr& expr) {
    throw std::runtime_error("ConstIntExpr unhandled");
}
void ASTPass::runOn(VariableExpr& expr) {
    throw std::runtime_error("VariableExpr unhandled");
}
void ASTPass::runOn(UnaryOpExpr& expr) {
    throw std::runtime_error("UnaryOpExpr unhandled");
}
void ASTPass::runOn(BinaryOpExpr& expr) {
    throw std::runtime_error("BinaryOpExpr unhandled");
}
void ASTPass::runOn(UnaryAssignOpExpr& expr) {
    throw std::runtime_error("UnaryAssignOpExpr unhandled");
}
void ASTPass::runOn(BinaryAssignOpExpr& expr) {
    throw std::runtime_error("BinaryAssignOpExpr unhandled");
}
