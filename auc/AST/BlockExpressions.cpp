/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "BlockExpressions.hpp"

#include <sstream>

using namespace AST;

ImperativeExprList BlockExpr::getBody() {
    return body;
}

void IfExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void WhileLoopExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}
