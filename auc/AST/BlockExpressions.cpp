/**
 * auc - The Aurum compiler
 * Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE.
 */

#include "BlockExpressions.hpp"

#include <sstream>

using namespace AST;

void IfExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void IfExpr::runPassOnChildren(ASTPass& pass) {
    for (ASTPtr<ImperativeExpr> expression : body) {
        expression->runPass(pass);
    }
}

void WhileLoopExpr::runPass(ASTPass& pass) {
    pass.runOn(*this);
}

void WhileLoopExpr::runPassOnChildren(ASTPass& pass) {
    for (ASTPtr<ImperativeExpr> expression : body) {
        expression->runPass(pass);
    }
}
