/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "Blocks.hpp"

#include <sstream>

using namespace AST;

StatementList Block::getBody() {
    return body;
}

void IfStmt::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void WhileLoop::runPass(ASTPass& pass) {
    pass.runOn(*this);
}
