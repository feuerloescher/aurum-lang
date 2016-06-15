/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "StdLibPass.hpp"
#include "AST/ScalarTypes.hpp"

using namespace AST;
using namespace Passes;

StdLibPass::StdLibPass(AST::AbstractSyntaxTree& ast) : ast(ast) {
}

void StdLibPass::run() {
    addStdLibTypes();
    /// more to come...
}

void StdLibPass::addStdLibTypes() {
    ast.getTypes().insert(std::make_shared<IntType>("uint32", 32, false));
}
