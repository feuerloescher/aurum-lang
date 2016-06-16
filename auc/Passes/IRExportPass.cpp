/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "IRExportPass.hpp"
#include "AST/ScalarTypes.hpp"

using namespace AST;
using namespace Passes;

IRExportPass::IRExportPass(AST::AbstractSyntaxTree& ast) : ast(ast) {
}

void IRExportPass::run() {
    ast.getLLVMModule().dump();
}
