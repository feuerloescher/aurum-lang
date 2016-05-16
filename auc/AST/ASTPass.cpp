/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTPass.hpp"

#include <stdexcept>

using namespace AST;

void ASTPass::runOn(DeclarativeExpr& expr) {
    throw std::runtime_error("Unknown DeclarativeExpr type");
}

void ASTPass::runOn(ImperativeExpr& expr) {
    throw std::runtime_error("Unknown ImperativeExpr type");
}

void ASTPass::runOn(BlockExpr& expr) {
    throw std::runtime_error("Unknown BlockExpr type");
}

void ASTPass::runOn(ValueExpr& expr) {
    throw std::runtime_error("Unknown ValueExpr type");
}
