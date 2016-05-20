/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "ASTPass.hpp"

#include <stdexcept>

using namespace AST;

void ASTPass::runOn(Declaration& expr) {
    throw std::runtime_error("Unknown Declaration type");
}

void ASTPass::runOn(Statement& expr) {
    throw std::runtime_error("Unknown Statement type");
}

void ASTPass::runOn(Block& expr) {
    throw std::runtime_error("Unknown Block type");
}

void ASTPass::runOn(Expression& expr) {
    throw std::runtime_error("Unknown Expression type");
}
