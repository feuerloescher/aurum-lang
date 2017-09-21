/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTPass.hpp"
#include "AST/ASTElement.hpp"

#include <stdexcept>
#include <iostream>

using namespace AST;

ASTPass::ASTPass(AbstractSyntaxTree& ast) : ast(ast) {
}

void ASTPass::handleError(ASTElement& elem, const ASTError& err) {
//    std::cerr << "Error " << err.what() << std::endl;
    std::cerr << elem.getCodeLocation().toString() << std::endl;
    throw err;
}

void ASTPass::runOn(FunctionDecl& expr) {
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

void ASTPass::runOn(TypeStmt& expr) {
    throw std::runtime_error("TypeStmt unhandled");
}

void ASTPass::runOn(BasicTypeStmt& expr) {
    throw std::runtime_error("BasicTypeStmt unhandled");
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
